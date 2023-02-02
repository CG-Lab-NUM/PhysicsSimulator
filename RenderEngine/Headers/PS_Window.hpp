#pragma once
#include "PS_RenderGeneric.hpp"
#include "PS_KeyboardHandler.hpp"
#include "PS_MouseHandler.hpp"

namespace ps {
	class PS_Window {
	public:
		PS_Window();
		PS_Window(uint32_t w, uint32_t h, std::string windowTitle);

		VkSurfaceKHR getSurface() {
			return surface;
		}
		GLFWwindow* getWindow() {
			return window;
		}
		glm::vec2 getSize();
		
		void setSize(int width, int height) {
			WIDTH = width;
			HEIGHT = height;
			glfwSetWindowSize(window, WIDTH, HEIGHT);
		}
		void cleanup();
		void createSurface(VkInstance instance);
		bool framebufferResized = false;

	private:
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

		GLFWwindow* window{};
		VkSurfaceKHR surface{};
		
		int WIDTH = 1024;
		int HEIGHT = 768;
	};
}