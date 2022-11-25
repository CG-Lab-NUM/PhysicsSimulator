#pragma once

#include "PS_Device.hpp"
#include "PS_Pipeline.hpp"
#include "PS_Window.hpp"

namespace ps {
	class PS_Test {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 800;

		void run();

	private:
		PS_Window psWindow{WIDTH, HEIGHT, "Hello Vulkan"};
		PS_Device psDevice{psWindow};
		PS_Pipeline psPipeline{
			psDevice, 
			"Shader/shader.vert.spv", 
			"Shader/shader.frag.spv",
			PS_Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
	};
}