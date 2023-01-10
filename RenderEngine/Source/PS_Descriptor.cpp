#include "PS_Descriptor.hpp"

namespace ps {
	PS_DescriptorSet::PS_DescriptorSet(PS_Device *device, uint32_t frames, uint32_t objectCount) {
		psDevice = device;
		maxFrames = frames;
		gameObjectCount = objectCount;
	}

	void PS_DescriptorSet::createLayout(VkDescriptorSetLayoutBinding binding) {
		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = 1;
		layoutInfo.pBindings = &binding;

		VkDescriptorSetLayout setLayout;
		if (vkCreateDescriptorSetLayout(psDevice->device, &layoutInfo, nullptr, &setLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create uniform descriptor set layout!");
		}
		setLayouts.push_back(setLayout);
	}

	void PS_DescriptorSet::createPool() {
		std::array<VkDescriptorPoolSize, 2> poolSizes{};
		poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[0].descriptorCount = maxFrames;
		poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[1].descriptorCount = gameObjectCount;

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = maxFrames + gameObjectCount;

		if (vkCreateDescriptorPool(psDevice->device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor pool!");
		}
	}

	void PS_DescriptorSet::createSets(std::vector<std::unique_ptr<PS_BufferHandler>> *buffers) {
		std::vector<VkDescriptorSetLayout> layouts(maxFrames, setLayouts[0]);
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = descriptorPool;
		allocInfo.descriptorSetCount = maxFrames;
		allocInfo.pSetLayouts = layouts.data();

		descriptorSets.resize(maxFrames);
		if (vkAllocateDescriptorSets(psDevice->device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		for (size_t i = 0; i < buffers->size(); i++) {
			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = buffers->at(i)->getBuffer();;
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(UniformBufferObject);

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = descriptorSets[i];
			descriptorWrite.dstBinding = 0;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pBufferInfo = &bufferInfo;

			vkUpdateDescriptorSets(psDevice->device, 1, &descriptorWrite, 0, nullptr);
		}
	}
}