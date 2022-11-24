#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace ps_window {
	class PS_Window {
	public:
		PS_Window(int w, int h, std::string name);
		~PS_Window();

		PS_Window(const PS_Window&) = delete;
		PS_Window &operator = (const PS_Window &) = delete;

		bool shouldClose() {
			return glfwWindowShouldClose(window);
		}

	private:
		void initWindow();

		const int width;
		const int height;
		std::string windowName;

		GLFWwindow* window;
	};
}