#include "PS_Window.hpp"

namespace ps_window {
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
}