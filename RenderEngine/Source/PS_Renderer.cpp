#include "PS_Renderer.hpp"

namespace ps {
	PS_Renderer::PS_Renderer(PS_GameLevel* gameLevel) {
		gameObjects = gameLevel->getGameObjects();
		psPipeline = new PS_Pipeline(&psWindow, &psDevice, &psSwapChain, gameObjects, gameLevel->getCamera());
	}

	void PS_Renderer::mainLoop() {
		while (!glfwWindowShouldClose(psWindow.getWindow())) {
			glfwPollEvents();
			psPipeline->drawFrame();
		}

		vkDeviceWaitIdle(psDevice.device);
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