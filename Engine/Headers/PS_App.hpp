#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "PS_Window.hpp"
#include "PS_Device.hpp"
#include "PS_Pipeline.hpp"
#include "PS_Loader.hpp"
#include "PS_GameLevel.hpp"

namespace ps {
	class PS_App {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 800;

		PS_App();
		PS_App(const PS_App&) = delete;
		PS_App& operator = (const PS_App&) = delete;

		void run();
		void setResized(bool b) {
			//psDevice.setFrameBufferResized(b);
		}

	private:
		void mainLoop();

		PS_Window psWindow{ WIDTH, HEIGHT, "Hello Vulkan" };
		PS_Device psDevice{};
		PS_Pipeline psPipeline{ &psDevice };

		PS_Loader psLoader{};
	};
}