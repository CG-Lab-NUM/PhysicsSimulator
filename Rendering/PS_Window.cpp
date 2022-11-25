#include "PS_Window.hpp"
#include <stdexcept>

namespace ps {
	PS_Window::PS_Window(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
		initWindow();
	};
	PS_Window::~PS_Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void PS_Window::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}

	void PS_Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create a window surface");
		}
	}
}