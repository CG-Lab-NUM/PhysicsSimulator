#include "PS_ModelHandler.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace ps {
	PS_ModelHandler::PS_ModelHandler(PS_Device* device) : PS_Allocator(device) {
		this->psDevice = device;
	}

	void PS_ModelHandler::loadModel(PS_GameObject* object) {
		PS_Material material = object->getMaterial();
		glm::vec4 color = material.getColor().color;
		bool isTexture = material.getColor().isTexture;

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
						vertex.color = color;
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
					uniqueVertices[vertex] = static_cast<uint32_t>(geometryObject.vertices.size());
					geometryObject.vertices.push_back(vertex);
				}

				geometryObject.indices.push_back(uniqueVertices[vertex]);
			}
		}
	}

	void PS_ModelHandler::loadLight(PS_Light* object) {
		std::unordered_map<Vertex, uint32_t> uniqueVertices{};
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;
		glm::vec3 color = object->getLightColor();

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, object->getModel().c_str())) {
			throw std::runtime_error(warn + err);
		}
		std::cout << "Light Loaded Model:" << object->getModel() << std::endl;

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex{};

				if (index.vertex_index >= 0) {
					vertex.pos = {
						(attrib.vertices[3 * index.vertex_index + 0] + object->getLocation().x) * object->getScale().x,
						(attrib.vertices[3 * index.vertex_index + 1] + object->getLocation().y) * object->getScale().y,
						(attrib.vertices[3 * index.vertex_index + 2] + object->getLocation().z) * object->getScale().z,
					};
					vertex.pos = rotate(object->getForwardVector(), vertex.pos, object->getRotation().x + object->getMeshRotation().x);
					vertex.pos = rotate(object->getRightVector(), vertex.pos, object->getRotation().y + object->getMeshRotation().y);
					vertex.pos = rotate(-object->getUpVector(), vertex.pos, object->getRotation().z + object->getMeshRotation().z);

					vertex.color = { color.x, color.y, color.z, -1 };
					if (index.texcoord_index >= 0) {
						vertex.texCoord = { -1, -1 };
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
					uniqueVertices[vertex] = static_cast<uint32_t>(geometryObject.vertices.size());
					geometryObject.vertices.push_back(vertex);
				}

				geometryObject.indices.push_back(uniqueVertices[vertex]);
			}
		}
	}

	void PS_ModelHandler::createVertexBuffer() {
		uint32_t vertexCount = static_cast<uint32_t>(geometryObject.vertices.size());
		VkDeviceSize bufferSize = sizeof(geometryObject.vertices[0]) * vertexCount;
		uint32_t vertexSize = sizeof(geometryObject.vertices[0]);

		PS_BufferHandler stagingBuffer{
			psDevice,
			vertexSize,
			vertexCount,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		};

		stagingBuffer.map();
		stagingBuffer.writeToBuffer((void*)geometryObject.vertices.data());
		
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
		uint32_t indexCount = static_cast<uint32_t>(geometryObject.indices.size());
		bool hasIndexBuffer = indexCount > 0;
		if (!hasIndexBuffer) {
			return;
		}
		VkDeviceSize bufferSize = sizeof(geometryObject.indices[0]) * geometryObject.indices.size();
		uint32_t indexSize = sizeof(geometryObject.indices[0]);

		PS_BufferHandler stagingBuffer{
			psDevice,
			indexSize,
			indexCount,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		};

		stagingBuffer.map();
		stagingBuffer.writeToBuffer((void*)geometryObject.indices.data());

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
		loadModel(object);
		createVertexBuffer();
		createIndexBuffer();
	}
	void PS_ModelHandler::Load(PS_Light* object) {
		loadLight(object);
		createVertexBuffer();
		createIndexBuffer();
	}

	void PS_ModelHandler::Destroy() {

	}

	void PS_ModelHandler::Render(VkCommandBuffer commandBuffer) {
		VkBuffer vertexBuffers[] = { vertexBuffer->getBuffer()};
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(commandBuffer, indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);
		vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(geometryObject.indices.size()), 1, 0, 0, 0);
	}

	glm::vec3 PS_ModelHandler::rotate(glm::vec3 axis, glm::vec3 point, float angle) {
		float norm = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
		axis = { axis.x / norm, axis.y / norm, axis.z / norm };
		glm::quat rotation = glm::angleAxis(glm::radians(angle), axis);
		glm::mat3 rotationMatrix = glm::mat3(rotation);
		return rotationMatrix * point;
	}
}