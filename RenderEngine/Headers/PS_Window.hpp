#pragma once
#include "PS_RenderGeneric.hpp"
#include "PS_KeyboardHandler.hpp"

namespace ps {
	class PS_Window {
	public:
		PS_Window();
		PS_Window(uint32_t w, uint32_t h, std::string windowTitle);
		~PS_Window();

		VkSurfaceKHR getSurface() {
			return surface;
		}
		GLFWwindow* getWindow() {
			return window;
		}

		void createSurface(VkInstance instance);

		bool framebufferResized = false;

	private:
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

		GLFWwindow* window{};
		VkSurfaceKHR surface{};
		
		uint32_t WIDTH = 1024;
		uint32_t HEIGHT = 768;

	};
}