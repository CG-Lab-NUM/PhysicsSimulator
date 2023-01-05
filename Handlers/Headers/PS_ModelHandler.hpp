#pragma once
#include "PS_Helper.hpp"

namespace ps {
	class PS_ModelHandler : PS_Helper {
	public:
		PS_ModelHandler(PS_Device* device);
		void Load(PS_GameObject* object);
		void Destroy();
		void Render(VkCommandBuffer commandBuffer);
		void setDevice(PS_Device* device) {
			this->psDevice = device;
		}

		PS_Device* psDevice;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;

	private:
		void loadModel(PS_GameObject* object);
		void createVertexBuffer();
		void createIndexBuffer();
	};
}