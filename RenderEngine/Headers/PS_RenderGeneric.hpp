#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <array>
#include <optional>
#include <set>
#include <unordered_map>
#include <map>

#define MAX_LIGHTS 10

namespace ps {
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct PointLight {
		glm::vec4 position;
		glm::vec4 color;
	};

	struct UniformBufferObject {
		alignas(16) glm::mat4 transform;
		alignas(16) glm::vec4 ambientLightColor;
		PointLight pointLights[MAX_LIGHTS];
		int numLights;
	};

	struct PushConstant {
		glm::mat4 modelMatrix{ 1.f };
		glm::mat4 normalMatrix{ 1.f };
		glm::mat4 lightMatrix{ 1.f };
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct Vertex {
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 texCoord;

		static VkVertexInputBindingDescription getBindingDescription();
		static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

		bool operator==(const Vertex& other) const;
	};

	struct GeometryObject3D {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};

	//void print3DVector(glm::vec3 vector, std::string preword) {
	//	std::cout << preword << " " << vector.x << " " << vector.y << " " << vector.z << std::endl;
	//}
}

namespace std {
	template<> struct hash<ps::Vertex> {
		size_t operator()(ps::Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}
