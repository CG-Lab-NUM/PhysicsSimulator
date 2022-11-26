#include "PS_Window.hpp"

namespace ps {
	PS_Window::PS_Window(int width, int height, std::string name) {
		WIDTH = width;
		HEIGHT = height;
		NAME = name;
		initWindow();
	}

	PS_Window::~PS_Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void PS_Window::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		window = glfwCreateWindow(WIDTH, HEIGHT, NAME.c_str(), nullptr, nullptr);
	}
}