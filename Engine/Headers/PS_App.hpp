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
		PS_GameObject gameObject1{ {0, 1.0f, 0}, {90, 0, 0}, {1, 1, 1} };
		PS_GameObject gameObject2{ {-1.0f, -1.0f, 0}, {0, 0, 0}, {1, 1, 1} };
		PS_GameObject gameObject3{ {0, -1.0f, 0}, {0, 0, 0}, {1, 1, 1} };
		PS_GameObject gameObject4{ {1.0f, -1.0f, 0}, {0, 0, 0}, {1, 1, 1} };
		std::vector<PS_GameObject*> gameObjects;
		PS_Window psWindow{ 800, 600, "CustomTitle" };
		PS_Device psDevice{ &psWindow };
		PS_SwapChain psSwapChain{ &psDevice, &psWindow };
		PS_Pipeline *psPipeline;
	};
}