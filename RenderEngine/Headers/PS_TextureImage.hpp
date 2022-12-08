#include "PS_Helper.hpp"

namespace ps {
	class PS_TextureImage : PS_Helper {
	public:
		PS_TextureImage(PS_Device* psDevice, VkDescriptorPool* descriptorPool, VkDescriptorSetLayout* textureDescriptorSetLayout);
		void Load(PS_GameObject* object);
		void Free();
		void Destroy();

		void setDevice(PS_Device* device) {
			this->psDevice = device;
		}

		VkDescriptorSet descriptorSet;
		
	private:
		PS_Device* psDevice;
		uint32_t mipLevels;
		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageView textureImageView;
		VkSampler textureSampler;

		VkDescriptorPool* descriptorPool;
		VkDescriptorSetLayout* textureDescriptorSetLayout;

		void createTextureImage(PS_GameObject* object);
		void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
		void createTextureImageView();
		void createTextureSampler();
		void createTextureDescriptorSet();
	};
}