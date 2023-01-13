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
		//topLeft.pos = { 0, 0, 0 };
		//topRight.pos = { 50.f, 0, 0 };
		//bottomLeft.pos = { 50.f, 0, 50 };
		//bottomRight.pos = { 0, 0, 50 };

		topLeft.color = { 1.0f, 1.0f, 1.0f, 1 };
		topRight.color = { 1.0f, 1.0f, 1.0f, 1 };
		bottomLeft.color = { 1.0f, 1.0f, 1.0f, 1 };
		bottomRight.color = { 1.0f, 1.0f, 1.0f, 1 };

		topLeft.type = 1;
		topRight.type = 1;
		bottomLeft.type = 1;
		bottomRight.type = 1;

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
		createVertexBuffer();
		createIndexBuffer();
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
		center = gameCamera->getCenter();
		y = gameCamera->getUpVector();
		x = gameCamera->getForwardVector();
		x = (-1.0f) * (glm::cross(y, x));
		z = gameCamera->getForwardVector();
		/*center[0] = center[0];
		center[1] = center[1];*/

		/*vertices[0].pos = {center[0], center[1], center[2]};
		vertices[1].pos = { center[0], center[1], center[2] };
		vertices[2].pos = { center[0], center[1], center[2] };
		vertices[3].pos = { center[0], center[1], center[2] };*/
		
		//std::cout << center.x << " " << center.y << std::endl;

		vertices[0].pos = { center[0], center[1], center[2] };
		vertices[1].pos = { center[0], center[1] + 10, center[2] };
		vertices[2].pos = { center[0] + 10, center[1] + 10, center[2] };
		vertices[3].pos = { center[0] + 10, center[1], center[2] };

		printVector("1", vertices[0].pos);
		printVector("2", vertices[1].pos);
		printVector("3", vertices[2].pos);
		printVector("4", vertices[3].pos);
		/*vertices[1].pos = { center[0] + h * y[0], center[1] + h * y[1], center[2] + h * y[2] };
		vertices[2].pos = { center[0] + ((-w) * x[0] + h * y[0]), center[1] + ((-w)*x[1] + h * y[1]), center[2] + ((-w) * x[2] + h * y[2]) };
		vertices[3].pos = { center[0] + (-w) * x[0], center[1] + (-w) * x[1], center[2] + (-w) * x[2] };*/
		
		//std::cout << "center: "<< vertices[0].pos.x << " " << vertices[0].pos.y << " " << vertices[0].pos.z << std::endl;
		std::cout << "camera center: " << gameCamera->getEye()[0] << " " << gameCamera->getEye()[1] << " " << gameCamera->getEye()[2] << std::endl;
		//std::cout << "camera center: " << gameCamera->getForwardVector()[0] << " " << gameCamera->getForwardVector()[1] << " " << gameCamera->getForwardVector()[2] << std::endl;
	}

	void UI_Widget::printVector(std::string label, glm::vec3 pos) {
		std::cout << label << ": " << pos.x << " " << pos.y << " " << pos.z << std::endl;
	}
}

/*


1: 16.4147 -8.00105 -14.0225
2: 16.4147 1.99895 -14.0225
3: 26.4147 1.99895 -14.0225
4: 26.4147 -8.00105 -14.0225

1: 15.8673 -8.27456 -14.0347
2: 15.8673 1.72544 -14.0347
3: 25.8673 1.72544 -14.0347


1: 15.8673 -8.27456 -14.0347
2: 15.8673 1.72544 -14.0347
3: 25.8673 1.72544 -14.0347
4: 25.8673 -8.27456 -14.0347

1: 15.8673 -8.27456 -14.0347
2: 15.8673 1.72544 -14.0347
3: 25.8673 1.72544 -14.0347
4: 25.8673 -8.27456 -14.0347

1: 15.8673 -8.27456 -14.0347
2: 15.8673 1.72544 -14.0347
3: 25.8673 1.72544 -14.0347
4: 25.8673 -8.27456 -14.0347

*/