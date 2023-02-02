#include "PS_Renderer.hpp"

namespace ps {
	PS_Renderer::PS_Renderer(PS_GameLevel* level) {
		currentPipeline = 0;
		gameLevel = level;
		gameObjects = gameLevel->getGameObjects();
		pipeline = new PS_Pipeline(&psWindow, &psDevice, &psSwapChain, gameObjects, gameLevel->getLights(), gameLevel->getCamera(), "Shaders/unlit_vert.spv", "Shaders/unlit_frag.spv", false);
	}

	void PS_Renderer::mainLoop() {
		while (!glfwWindowShouldClose(psWindow.getWindow())) {
			tick();
			glfwPollEvents();
			drawFrame();
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

	void PS_Renderer::drawFrame() {
		if (currentPipeline != gameLevel->getPipeline()) {
			currentPipeline = gameLevel->getPipeline();
			changePipeline();
		}
		pipeline->drawFrame();
	}

	void PS_Renderer::changePipeline() {
		if (currentPipeline == LIT_PIPELINE) {
			pipeline = new PS_Pipeline(&psWindow, &psDevice, &psSwapChain, gameObjects, gameLevel->getLights(), gameLevel->getCamera(), "Shaders/lit_vert.spv", "Shaders/lit_frag.spv", false);
		}
		else {
			pipeline = new PS_Pipeline(&psWindow, &psDevice, &psSwapChain, gameObjects, gameLevel->getLights(), gameLevel->getCamera(), "Shaders/unlit_vert.spv", "Shaders/unlit_frag.spv", false);
		}
	}
}