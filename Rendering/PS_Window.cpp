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

	void PS_Window::createSurface(VkInstance instance, VkDevice device) {
		VkWin32SurfaceCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hwnd = glfwGetWin32Window(window);
		createInfo.hinstance = GetModuleHandle(nullptr);
		
		if (vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
		else {
			std::cout << "Window Surface created...\n";
		}
	}
}