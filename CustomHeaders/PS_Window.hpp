#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <iostream>
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