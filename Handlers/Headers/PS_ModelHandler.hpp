#pragma once
#include "PS_Allocator.hpp"
#include "PS_BufferHandler.hpp"
#include <memory>

namespace ps {
	class PS_ModelHandler : PS_Allocator {
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
		std::unique_ptr<PS_BufferHandler> vertexBuffer;
		std::unique_ptr<PS_BufferHandler> indexBuffer;

	private:
		void loadModel(PS_GameObject* object);
		void createVertexBuffer();
		void createIndexBuffer();
	};
}