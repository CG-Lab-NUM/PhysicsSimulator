#include "PS_Window.hpp"
#include <stdexcept>

namespace ps {
	PS_Window::PS_Window() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		PS_KeyboardHandler::setLetterEnabled(true);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);

		// Callbacks
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
		glfwSetKeyCallback(window, PS_KeyboardHandler::keyCallback);
	}

	PS_Window::PS_Window(uint32_t w, uint32_t h, std::string windowTitle) {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		WIDTH = w;
		HEIGHT = h;

		window = glfwCreateWindow(WIDTH, HEIGHT, windowTitle.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);

		// Callbacks
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
		glfwSetKeyCallback(window, PS_KeyboardHandler::keyCallback);
		glfwSetCursorPosCallback(window, PS_MouseHandler::positionCallback);
		glfwSetCursorEnterCallback(window, PS_MouseHandler::enterCallback);
		glfwSetMouseButtonCallback(window, PS_MouseHandler::buttonCallback);
	}

	void PS_Window::cleanup() {
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