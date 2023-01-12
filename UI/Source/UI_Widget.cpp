#include "UI_Widget.hpp"

namespace ps {
	UI_Widget::UI_Widget(PS_Device* device, PS_GameCamera *camera) : PS_Allocator(device) {
		psDevice = device;
		gameCamera = camera;
		this->vertices = vertices;
		this->indices = indices;
		createWidget();
		createVertexBuffer();
		createIndexBuffer();
	}

	void UI_Widget::createWidget() {
		GeometrySquare object;
		object.x = 0;
		object.y = 0;
		object.height = 100;
		object.width = 100;
		renderComponent = object;
		
		Vertex topLeft, topRight, bottomLeft, bottomRight;
		topLeft.pos = { -50, -5, 0 };
		topRight.pos = { 50.f, -5, 0 };
		bottomLeft.pos = { 50.f, -5, 50 };
		bottomRight.pos = { -50.0f, -5, 50};

		topLeft.color = { 1.0f, 0.0f, 0.0f, 0.5f };
		topRight.color = { 1.0f, 0.0f, 0.0f, 0.5f };
		bottomLeft.color = { 1.0f, 0.0f, 0.0f, 0.5f };
		bottomRight.color = { 1.0f, 0.0f, 0.0f, 0.5f };

		topLeft.type = 1;
		topRight.type = 1;
		bottomLeft.type = 1;
		bottomRight.type = 1;

		vertices.push_back(topLeft);
		vertices.push_back(topRight);
		vertices.push_back(bottomLeft);
		vertices.push_back(bottomRight);
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(0);
	}

	void UI_Widget::createVertexBuffer() {
		uint32_t vertexCount = static_cast<uint32_t>(vertices.size());
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
		uint32_t vertexSize = sizeof(vertices[0]);

		PS_BufferHandler stagingBuffer{
			psDevice,
			vertexSize,
			vertexCount,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		};

		stagingBuffer.map();
		stagingBuffer.writeToBuffer((void*)vertices.data());

		vertexBuffer = std::make_unique<PS_BufferHandler>(
			psDevice,
			vertexSize,
			vertexCount,
			VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
			);

		copyBuffer(stagingBuffer.getBuffer(), vertexBuffer->getBuffer(), bufferSize);
	}
	void UI_Widget::createIndexBuffer() {
		uint32_t indexCount = static_cast<uint32_t>(indices.size());
		bool hasIndexBuffer = indexCount > 0;
		if (!hasIndexBuffer) {
			return;
		}
		VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
		uint32_t indexSize = sizeof(indices[0]);

		PS_BufferHandler stagingBuffer{
			psDevice,
			indexSize,
			indexCount,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		};

		stagingBuffer.map();
		stagingBuffer.writeToBuffer((void*)indices.data());

		indexBuffer = std::make_unique<PS_BufferHandler>(
			psDevice,
			indexSize,
			indexCount,
			VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
			);

		copyBuffer(stagingBuffer.getBuffer(), indexBuffer->getBuffer(), bufferSize);
	}

	void UI_Widget::renderWidget(VkCommandBuffer commandBuffer) {
		translateGeometry();
		VkBuffer vertexBuffers[] = { vertexBuffer->getBuffer() };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(commandBuffer, indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);
		vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
	}

	void UI_Widget::translateGeometry() {

	}
}