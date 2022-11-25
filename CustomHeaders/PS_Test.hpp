#pragma once

#include "PS_Device.hpp"
#include "PS_Pipeline.hpp"
#include "PS_Window.hpp"
#include "PS_SwapChain.hpp"

#include <memory>

namespace ps {
	class PS_Test {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 800;

		PS_Test();
		~PS_Test();

		PS_Test(const PS_Test&) = delete;
		PS_Test& operator = (const PS_Test&) = delete;
		void run();

	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		PS_Window psWindow{WIDTH, HEIGHT, "Hello Vulkan"};
		PS_Device psDevice{psWindow};
		PS_SwapChain psSwapchain{ psDevice, psWindow.getExtent() };

		std::unique_ptr<PS_Pipeline> psPipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}