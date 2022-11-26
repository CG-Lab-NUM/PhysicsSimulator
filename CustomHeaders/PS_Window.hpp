#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include "PS_Logger.hpp"

namespace ps {
	class PS_Window {
	public:
		PS_Window(int width, int height, std::string name);
		~PS_Window();

		PS_Window(const PS_Window&) = delete;
		PS_Window& operator = (const PS_Window&) = delete;

		void initWindow();
		GLFWwindow* getWindow() {
			return window;
		}

	private:
		int WIDTH;
		int HEIGHT;
		std::string NAME;
		GLFWwindow* window;
	};
}