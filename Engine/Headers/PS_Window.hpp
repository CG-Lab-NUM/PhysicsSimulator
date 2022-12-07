#pragma once
#include "PS_EngineGeneric.hpp"

namespace ps {
	class PS_Window {
	public:
		PS_Window();
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
		
		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;
	};
}