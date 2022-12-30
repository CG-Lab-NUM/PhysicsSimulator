#pragma once
#include "PS_KeyboardHandler.hpp"
#include "PS_RenderGeneric.hpp"

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
		static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

		GLFWwindow* window{};
		VkSurfaceKHR surface{};
		PS_KeyboardHandler keyboardHandler{};
		
		uint32_t WIDTH = 1024;
		uint32_t HEIGHT = 768;
	};
}