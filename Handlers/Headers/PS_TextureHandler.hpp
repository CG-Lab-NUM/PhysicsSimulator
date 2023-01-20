#pragma once
#include "PS_Allocator.hpp"
#include "PS_BufferHandler.hpp"

namespace ps {
	class PS_TextureHandler : PS_Allocator {
	public:
		PS_TextureHandler(PS_Device* psDevice, VkDescriptorPool* descriptorPool);
		void Load(std::string texturePath);
		void Free();
		void createLayouts();
		void Destroy();

		void setDevice(PS_Device* device) {
			this->psDevice = device;
		}

		VkDescriptorSet descriptorSet;
		VkDescriptorSetLayout textureDescriptorSetLayout;

		VkImage getTextureImage() {
			return textureImage;
		}
		VkDeviceMemory getTextureImageMemory() {
			return textureImageMemory;
		}
		VkImageView getTextureImageView() {
			return textureImageView;
		}
		VkSampler getTextureSampler() {
			return textureSampler;
		}
	private:
		PS_Device* psDevice;
		uint32_t mipLevels;

		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageView textureImageView;
		VkSampler textureSampler;

		VkImage emissiveImage;
		VkDeviceMemory emissiveImageMemory;
		VkImageView emissiveImageView;
		VkSampler emissiveSampler;

		VkDescriptorPool* descriptorPool;

		std::string texturePath;
		
		bool isEmissive;

		void createTextureImage();
		void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
		void createTextureImageView();
		void createTextureSampler();
		void createTextureDescriptorSet();
	};
}