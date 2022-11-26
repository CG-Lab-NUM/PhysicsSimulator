#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "PS_Window.hpp"
#include "PS_Device.hpp"

namespace ps {
	class PS_App {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 800;

		PS_App();
		~PS_App();
		PS_App(const PS_App&) = delete;
		PS_App& operator = (const PS_App&) = delete;

		void run();

	private:
		void initVulkan();
		void mainLoop();
		void cleanup();

		PS_Window psWindow{ WIDTH, HEIGHT, "Hello Vulkan" };
		PS_Device psDevice{};
	};
}