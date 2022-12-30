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

	PS_Window::PS_Window(uint32_t w, uint32_t h, std::string windowTitle) {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		WIDTH = w;
		HEIGHT = h;

		window = glfwCreateWindow(WIDTH, HEIGHT, windowTitle.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
		glfwSetKeyCallback(window, keyCallback);
	}

	PS_Window::~PS_Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void PS_Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto app = reinterpret_cast<PS_Window*>(glfwGetWindowUserPointer(window));
		app->framebufferResized = true;
	}

	void PS_Window::keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
		if (key == GLFW_KEY_E && action == GLFW_PRESS) {
			std::cout << "Temp\n";
		}
	}

	void PS_Window::createSurface(VkInstance instance) {
		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}
}