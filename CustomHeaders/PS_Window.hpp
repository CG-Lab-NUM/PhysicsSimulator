#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <vector>
#include <array>
#include "PS_Logger.hpp"

namespace ps {
	class PS_Window {
	public:
		PS_Window(int width, int height, std::string name);
		~PS_Window();

		PS_Window(const PS_Window&) = delete;
		PS_Window& operator = (const PS_Window&) = delete;

		void initWindow();
		void createSurface(VkInstance instance, VkDevice device);

		struct Vertex {
			glm::vec2 pos;
			glm::vec3 color;

			static VkVertexInputBindingDescription getBindingDescription() {
				VkVertexInputBindingDescription bindingDescription{};
				bindingDescription.binding = 0;
				bindingDescription.stride = sizeof(Vertex);
				bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

				return bindingDescription;
			}

			static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
				std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

				attributeDescriptions[0].binding = 0;
				attributeDescriptions[0].location = 0;
				attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
				attributeDescriptions[0].offset = offsetof(Vertex, pos);

				attributeDescriptions[1].binding = 0;
				attributeDescriptions[1].location = 1;
				attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
				attributeDescriptions[1].offset = offsetof(Vertex, color);

				return attributeDescriptions;
			}
		};

		struct UniformBufferObject {
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 proj;
		};

		//
		// Getters
		//
		GLFWwindow* getWindow() {
			return window;
		}
		VkSurfaceKHR getSurface() {
			return surface;
		}

	private:
		int WIDTH;
		int HEIGHT;
		std::string NAME;
		GLFWwindow* window;
		VkSurfaceKHR surface;

		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	};
}