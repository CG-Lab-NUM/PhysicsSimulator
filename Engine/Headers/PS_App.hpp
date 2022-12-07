#pragma once
#include "PS_Pipeline.hpp"

namespace ps {
	class PS_App {
	public:
		PS_App();
		~PS_App();

		void run();
		void mainLoop();
		void cleanup();

	private:
		PS_Window psWindow{};
		PS_Device psDevice{ &psWindow };
		PS_SwapChain psSwapChain{ &psDevice, &psWindow };
		PS_Pipeline psPipeline { &psWindow, &psDevice, &psSwapChain};
	};
}