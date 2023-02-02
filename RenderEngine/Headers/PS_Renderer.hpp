#pragma once
#include "PS_Pipeline.hpp"

namespace ps {
	class PS_Renderer {
	public:
		PS_Renderer(PS_GameLevel *level);

		void run();
		void mainLoop();
		void cleanup();

	private:
		void tick();
		void drawFrame();
		void changePipeline();

		PS_Window psWindow{ 1024, 768, "CustomTitle" };
		PS_Device psDevice{ &psWindow };
		PS_SwapChain psSwapChain{ &psDevice, &psWindow };
		PS_Pipeline *pipeline;
		PS_GameLevel *gameLevel;
		std::vector<PS_GameObject*> gameObjects;
		int currentPipeline;
	};
}