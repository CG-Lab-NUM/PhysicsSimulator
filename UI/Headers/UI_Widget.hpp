#pragma once
#include "PS_BufferHandler.hpp"

namespace ps {
	class UI_Widget : public PS_Allocator {
	public:
		UI_Widget(PS_Device* device);
		void renderWidget(VkCommandBuffer commandBuffer) {
			VkBuffer vertexBuffers[] = { vertexBuffer->getBuffer() };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(commandBuffer, indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);
			vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
		}

	private:
		void createWidget();
		void createVertexBuffer();
		void createIndexBuffer();

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::unique_ptr<PS_BufferHandler> vertexBuffer;
		std::unique_ptr<PS_BufferHandler> indexBuffer;

		PS_Device* psDevice;
	};
}