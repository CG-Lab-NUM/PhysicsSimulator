#include "PS_Window.hpp"
#include <stdexcept>

namespace ps {
	PS_Window::PS_Window() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	}

	PS_Window::~PS_Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void PS_Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto app = reinterpret_cast<PS_Window*>(glfwGetWindowUserPointer(window));
		app->framebufferResized = true;
	}

	void PS_Window::createSurface(VkInstance instance) {
		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}
}