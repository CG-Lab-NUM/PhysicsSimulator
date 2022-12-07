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
		PS_GameObject gameObject;
		PS_GameObject gameObject1{ {0, 0, 0}, {0, 0, 0}, {1, 2, 1} };
		PS_GameObject gameObject2{ {0, 0, 0}, {0, 0, 0}, {1, 1, 2} };
		PS_GameObject gameObject3{ {0, 0, 0}, {0, 0, 0}, {2, 1, 1} };
		std::vector<PS_GameObject*> gameObjects;
		std::vector<PS_GameObject*> gameObjects1;
		PS_Window psWindow{};
		PS_Device psDevice{ &psWindow };
		PS_SwapChain psSwapChain{ &psDevice, &psWindow };
		PS_Pipeline *psPipeline;
		PS_Pipeline* psPipeline1;
		//PS_Pipeline psPipeline1 { &psWindow, &psDevice, &psSwapChain, &gameObject1, false };
	};
}