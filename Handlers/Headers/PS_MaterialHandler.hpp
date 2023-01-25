#pragma once
#include "PS_Allocator.hpp"
#include "PS_BufferHandler.hpp"
#include "PS_Material.hpp"
#include "PS_Descriptor.hpp"

namespace ps {
	class PS_MaterialHandler : PS_Allocator {
	public:
		PS_MaterialHandler(PS_Device* device, PS_DescriptorSet* descriptorSet);
		void Load(PS_Material material);
		void Free();
		void createLayouts();
		void Destroy();

		void setDevice(PS_Device* device) {
			this->psDevice = device;
		}

		VkDescriptorSet descriptorSet;
		VkDescriptorSetLayout textureDescriptorSetLayout;

		VkImage getTextureImage(int i) {
			return textureImage[i];
		}
		VkDeviceMemory getTextureImageMemory(int i) {
			return textureImageMemory[i];
		}
		VkImageView getTextureImageView(int i) {
			return textureImageView[i];
		}
		VkSampler getTextureSampler(int i) {
			return textureSampler[i];
		}
	private:
		PS_Device* psDevice;
		PS_DescriptorSet* psDescriptor;
		uint32_t mipLevels;

		VkImage textureImage[2];
		VkDeviceMemory textureImageMemory[2];
		VkImageView textureImageView[2];
		VkSampler textureSampler[2];
		std::string texturePaths[2];
		//std::vector<std::string> texturePaths;
		bool validTexture[2];

		void createTextures(PS_Material material);
		void createTextureImage();
		void createMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
		void createTextureImageView();
		void createTextureSampler();
		void createTextureDescriptorSet();
	};
}