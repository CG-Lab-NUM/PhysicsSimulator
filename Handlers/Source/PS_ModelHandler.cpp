#include "PS_ModelHandler.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace ps {
	PS_ModelHandler::PS_ModelHandler(PS_Device* device) : PS_Allocator(device) {
		this->psDevice = device;
	}

	void PS_ModelHandler::loadModel(PS_GameObject* object) {
		std::unordered_map<Vertex, uint32_t> uniqueVertices{};
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, object->getModel().c_str())) {
			throw std::runtime_error(warn + err);
		}
		std::cout << "Loaded Model:" << object->getModel() << std::endl;

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex{};

				if (index.vertex_index >= 0) {
					vertex.pos = {
						(attrib.vertices[3 * index.vertex_index + 0] + object->getLocation()[0])* object->getScale()[0],
						(attrib.vertices[3 * index.vertex_index + 1] + object->getLocation()[1])* object->getScale()[1],
						(attrib.vertices[3 * index.vertex_index + 2] + object->getLocation()[2])* object->getScale()[2],
					};
					if (isTexture) {
						vertex.color = {
							attrib.colors[3 * index.vertex_index + 0],
							attrib.colors[3 * index.vertex_index + 1],
							attrib.colors[3 * index.vertex_index + 2],
							object->getAlpha()
						};
						if (index.texcoord_index >= 0) {
							vertex.texCoord = {
								attrib.texcoords[2 * index.texcoord_index + 0],
								1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
							};
						}
					}
					else {
						vertex.color = glm::vec4(color, 1);
						if (index.texcoord_index >= 0) {
							vertex.texCoord = { -1, -1 };
						}
					}
				}
				if (index.normal_index >= 0) {
					vertex.normal = {
						attrib.normals[3 * index.normal_index + 0],
						attrib.normals[3 * index.normal_index + 1],
						attrib.normals[3 * index.normal_index + 2],
					};
				}

				if (uniqueVertices.count(vertex) == 0) {
					uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(vertex);
				}

				indices.push_back(uniqueVertices[vertex]);
			}
		}
	}

	void PS_ModelHandler::createVertexBuffer() {
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
		stagingBuffer.writeToBuffer((void*) vertices.data());
		
		vertexBuffer = std::make_unique<PS_BufferHandler>(
			psDevice,
			vertexSize,
			vertexCount,
			VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
		);

		copyBuffer(stagingBuffer.getBuffer(), vertexBuffer->getBuffer(), bufferSize);
	}

	void PS_ModelHandler::createIndexBuffer() {
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

	void PS_ModelHandler::Load(PS_GameObject* object) {
		isTexture = true;
		loadModel(object);
		createVertexBuffer();
		createIndexBuffer();
	}

	void PS_ModelHandler::Load(PS_GameObject* object, glm::vec3 color) {
		isTexture = false;
		this->color = color;
		loadModel(object);
		createVertexBuffer();
		createIndexBuffer();
	}

	void PS_ModelHandler::Destroy() {

	}

	void PS_ModelHandler::Render(VkCommandBuffer commandBuffer){
		VkBuffer vertexBuffers[] = { vertexBuffer->getBuffer()};
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(commandBuffer, indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);
		vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
	}
}