#pragma once
#include "PS_Allocator.hpp"
#include "PS_BufferHandler.hpp"

namespace ps {
	class PS_DescriptorSet {
	public:
		PS_DescriptorSet(PS_Device *device, uint32_t frames, uint32_t objectCount);
		int createLayout(VkDescriptorSetLayoutBinding binding);
		int createLayout(std::vector<VkDescriptorSetLayoutBinding> binding);
		void createPool();
		void createSets(std::vector<std::unique_ptr<PS_BufferHandler>> *buffers);

		VkDescriptorSetLayout getSetLayout(int i) {
			return setLayouts[i];
		}
		VkDescriptorPool getPool() {
			return descriptorPool;
		}
		VkDescriptorSetLayout* getSetLayoutReference(int i) {
			return &setLayouts[i];
		}
		VkDescriptorPool* getPoolReference() {
			return &descriptorPool;
		}
		VkDescriptorSet* getSetReference(int i) {
			if (i < descriptorSets.size()) {
				return &descriptorSets[i];
			}
			return &descriptorSets[0];
		}
		std::vector<VkDescriptorSetLayout> getSetLayouts() {
			return setLayouts;
		}
		VkDescriptorPool descriptorPool;

	private:
		PS_Device* psDevice;
		uint32_t maxFrames;
		uint32_t gameObjectCount;
		int bindingCount;

		std::vector<VkDescriptorSetLayout> setLayouts;
		std::vector<VkDescriptorSet> descriptorSets;
		std::vector<VkDescriptorType> descriptorTypes;
	};
}