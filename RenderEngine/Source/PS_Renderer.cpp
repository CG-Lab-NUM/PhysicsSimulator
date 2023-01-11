#include "PS_Renderer.hpp"

namespace ps {
	PS_Renderer::PS_Renderer(PS_GameLevel* level) {
		gameLevel = level;
		gameObjects = gameLevel->getGameObjects();
		unlitPipeline = new PS_Pipeline(&psWindow, &psDevice, &psSwapChain, gameObjects, gameLevel->getCamera(), "Shaders/unlit_vert.spv", "Shaders/unlit_frag.spv");
		litPipeline = new PS_Pipeline(&psWindow, &psDevice, &psSwapChain, gameObjects, gameLevel->getCamera(), "Shaders/lit_vert.spv", "Shaders/lit_frag.spv");
	}

	void PS_Renderer::mainLoop() {
		while (!glfwWindowShouldClose(psWindow.getWindow())) {
			glfwPollEvents();
			if (gameLevel->getPipeline() == LIT_PIPELINE) {
				litPipeline->drawFrame();
			}
			else {
				unlitPipeline->drawFrame();
			}
			tick();
		}
		vkDeviceWaitIdle(psDevice.device);
	}

	void PS_Renderer::tick() {
		gameLevel->tick();
		gameLevel->getCamera()->tick();
		for (int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i]->tick();
		}
	}

	void PS_Renderer::cleanup() {
		psSwapChain.cleanup();
        //psPipeline->cleanup();
		psDevice.cleanup();
		psWindow.cleanup();
	}

	void PS_Renderer::run() {
		mainLoop();
		cleanup();
	}
}