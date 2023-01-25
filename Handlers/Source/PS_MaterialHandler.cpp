#include "PS_MaterialHandler.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define BASE_COLOR 0
#define EMISSIVE 1

namespace ps {
	PS_MaterialHandler::PS_MaterialHandler(PS_Device* device, PS_DescriptorSet *descriptorSet) : PS_Allocator(device) {
		psDevice = device;
		psDescriptor = descriptorSet;
	}

	void PS_MaterialHandler::createTextureImage() {
		int texWidth, texHeight, texChannels;
		for (int i = 0; i < 2; i++) {
			if (texturePaths[i].empty() or !validTexture[i]) {
				continue;
			}
			stbi_uc* pixels = stbi_load(texturePaths[i].c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

			VkDeviceSize imageSize = texWidth * texHeight * 4;
			mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;
			std::cout << "Loaded Texture: " << texturePaths[i] << std::endl;
			if (!pixels) {
				throw std::runtime_error("failed to load texture image!");
			}

			PS_BufferHandler stagingBuffer{
				psDevice,
				static_cast<size_t>(imageSize),
				1,
				VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
			};
			stagingBuffer.map();
			stagingBuffer.writeToBuffer((void*)pixels);

			stbi_image_free(pixels);
			createImage(texWidth, texHeight, mipLevels, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL,
				VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage[i], textureImageMemory[i]);
			transitionImageLayout(textureImage[i], VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);
			copyBufferToImage(stagingBuffer.getBuffer(), textureImage[i], static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
			//transitioned to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL while generating mipmaps

			createMipmaps(textureImage[i], VK_FORMAT_R8G8B8A8_SRGB, texWidth, texHeight, mipLevels);
		}
	}

	void PS_MaterialHandler::createMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels) {
		// Check if image format supports linear blitting
		VkFormatProperties formatProperties;
		vkGetPhysicalDeviceFormatProperties(psDevice->physicalDevice, imageFormat, &formatProperties);

		if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) {
			throw std::runtime_error("texture image format does not support linear blitting!");
		}

		VkCommandBuffer commandBuffer = beginSingleTimeCommands();

		VkImageMemoryBarrier barrier{};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.image = image;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;
		barrier.subresourceRange.levelCount = 1;

		int32_t mipWidth = texWidth;
		int32_t mipHeight = texHeight;

		for (uint32_t i = 1; i < mipLevels; i++) {
			barrier.subresourceRange.baseMipLevel = i - 1;
			barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

			vkCmdPipelineBarrier(commandBuffer,
				VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
				0, nullptr,
				0, nullptr,
				1, &barrier);

			VkImageBlit blit{};
			blit.srcOffsets[0] = { 0, 0, 0 };
			blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
			blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			blit.srcSubresource.mipLevel = i - 1;
			blit.srcSubresource.baseArrayLayer = 0;
			blit.srcSubresource.layerCount = 1;
			blit.dstOffsets[0] = { 0, 0, 0 };
			blit.dstOffsets[1] = { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 };
			blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			blit.dstSubresource.mipLevel = i;
			blit.dstSubresource.baseArrayLayer = 0;
			blit.dstSubresource.layerCount = 1;

			vkCmdBlitImage(commandBuffer,
				image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
				image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				1, &blit,
				VK_FILTER_LINEAR);

			barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			vkCmdPipelineBarrier(commandBuffer,
				VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
				0, nullptr,
				0, nullptr,
				1, &barrier);

			if (mipWidth > 1) mipWidth /= 2;
			if (mipHeight > 1) mipHeight /= 2;
		}

		barrier.subresourceRange.baseMipLevel = mipLevels - 1;
		barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		vkCmdPipelineBarrier(commandBuffer,
			VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
			0, nullptr,
			0, nullptr,
			1, &barrier);

		endSingleTimeCommands(commandBuffer);
	}

	void PS_MaterialHandler::createTextureImageView() {
		for (int i = 0; i < 2; i++) {
			if (!validTexture[i]) {
				continue;
			}
			textureImageView[i] = createImageView(textureImage[i], VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, mipLevels);
		}
	}

	void PS_MaterialHandler::createTextureSampler() {
		VkPhysicalDeviceProperties properties{};
		vkGetPhysicalDeviceProperties(psDevice->physicalDevice, &properties);

		for (int i = 0; i < 2; i++) {
			if (!validTexture[i]) {
				continue;
			}
			VkSamplerCreateInfo samplerInfo{};
			samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			samplerInfo.magFilter = VK_FILTER_LINEAR;
			samplerInfo.minFilter = VK_FILTER_LINEAR;
			samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			samplerInfo.anisotropyEnable = VK_TRUE;
			samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
			samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			samplerInfo.unnormalizedCoordinates = VK_FALSE;
			samplerInfo.compareEnable = VK_FALSE;
			samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
			samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
			samplerInfo.minLod = 0.0f;
			samplerInfo.maxLod = static_cast<float>(mipLevels);
			samplerInfo.mipLodBias = 0.0f;

			if (vkCreateSampler(psDevice->device, &samplerInfo, nullptr, &textureSampler[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create texture sampler!");
			}
		}
	}

	void PS_MaterialHandler::createTextureDescriptorSet() {
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = psDescriptor->descriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &textureDescriptorSetLayout;

		if (vkAllocateDescriptorSets(psDevice->device, &allocInfo, &descriptorSet) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		for (int i = 0; i < 2; i++) {
			if (!validTexture[i]) {
				continue;
			}
			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = textureImageView[i];
			imageInfo.sampler = textureSampler[i];

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = descriptorSet;
			descriptorWrite.dstBinding = i;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pImageInfo = &imageInfo;

			vkUpdateDescriptorSets(psDevice->device, 1, &descriptorWrite, 0, nullptr);
		}
	}

	void PS_MaterialHandler::Destroy() {
		for (int i = 0; i < 2; i++) {
			vkDestroySampler(psDevice->device, textureSampler[i], nullptr);
			vkDestroyImageView(psDevice->device, textureImageView[i], nullptr);
			vkDestroyImage(psDevice->device, textureImage[i], nullptr);
			vkFreeMemory(psDevice->device, textureImageMemory[i], nullptr);
		}
	}

	void PS_MaterialHandler::Free()
	{
		vkFreeDescriptorSets(psDevice->device, psDescriptor->descriptorPool, 1, &descriptorSet);
	}

	void PS_MaterialHandler::Load(PS_Material material) {
		createTextures(material);
		createLayouts();
		createTextureImage();
		createTextureImageView();
		createTextureSampler();
		createTextureDescriptorSet();
	}

	void PS_MaterialHandler::createLayouts() {
		VkDescriptorSetLayoutBinding baseColorBinding{
			0,
			VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			1,
			VK_SHADER_STAGE_FRAGMENT_BIT,
			nullptr
		};
		VkDescriptorSetLayoutBinding emissiveColorBinding{
			1,
			VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			1,
			VK_SHADER_STAGE_FRAGMENT_BIT,
			nullptr
		};
		std::vector<VkDescriptorSetLayoutBinding> bindings = { baseColorBinding, emissiveColorBinding };

		int bindingCount = bindings.size();
		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = (uint32_t)bindingCount;
		layoutInfo.pBindings = bindings.data();
		if (vkCreateDescriptorSetLayout(psDevice->device, &layoutInfo, nullptr, &textureDescriptorSetLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create uniform descriptor set layout!");
		}
	}

	void PS_MaterialHandler::createTextures(PS_Material material) {
		MaterialComponent component = material.getColor();
		if (component.isTexture) {
			texturePaths[BASE_COLOR] = component.texturePath;
			//texturePaths.push_back(component.texturePath);
			validTexture[BASE_COLOR] = true;
		}
		component = material.getEmissive();
		if (component.isTexture) {
			texturePaths[EMISSIVE] = component.texturePath;
			//texturePaths.push_back(component.texturePath);
			validTexture[EMISSIVE] = true;
		}
	}
}