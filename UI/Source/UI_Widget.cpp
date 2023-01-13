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
		GeometryObject2D object;
		object.x = 0;
		object.y = 0;
		object.height = 100;
		object.width = 100;
		renderComponent = object;
		

		Vertex topLeft, topRight, bottomLeft, bottomRight;
		topLeft.pos = { 0, 0, 0 };
		topRight.pos = { 50.f, 0, 0 };
		bottomLeft.pos = { 50.f, 0, 50 };
		bottomRight.pos = { 0, 0, 50 };

		topLeft.color = { 1.0f, 1.0f, 1.0f, 1 };
		topRight.color = { 1.0f, 1.0f, 1.0f, 1 };
		bottomLeft.color = { 1.0f, 1.0f, 1.0f, 1 };
		bottomRight.color = { 1.0f, 1.0f, 1.0f, 1 };

		vertices.push_back(bottomLeft);
		vertices.push_back(topLeft);
		vertices.push_back(topRight);
		vertices.push_back(bottomRight);
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(0);
		translateGeometry();
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
		glm::vec3 center, x, y, z; 
		float h = renderComponent.height; 
		float w = renderComponent.width;
		center = (gameCamera->getEye() + 10.0f * gameCamera->getForwardVector());
		y = gameCamera->getUpVector();
		x = gameCamera->getForwardVector();
		x = (-1.0f) * (glm::cross(y, x));
		z = gameCamera->getForwardVector();
		renderComponent.x = center[0];
		renderComponent.y = center[1];

		vertices[0].pos = { renderComponent.x, renderComponent.y, center[2] };
		vertices[1].pos = { renderComponent.x + h * y[0], renderComponent.y + h * y[1], center[2] + h * y[2] };
		vertices[2].pos = { renderComponent.x + ((-w) * x[0] + renderComponent.height * y[0]), renderComponent.y + ((-w)*x[1] + h * y[1]), center[2] + ((-w) * x[2] + h * y[2]) };
		vertices[3].pos = { renderComponent.x + (-w) * x[0], renderComponent.y + (-w) * x[1], center[2] + (-w) * x[2] };
		
		
		/*std::cout << "center: "<< vertices[0].pos.x << " " << vertices[0].pos.y << " " << vertices[0].pos.z << std::endl;
		std::cout << "camera center: " << gameCamera->getEye()[0] << " " << gameCamera->getEye()[1] << " " << gameCamera->getEye()[2] << std::endl;*/
	}
}