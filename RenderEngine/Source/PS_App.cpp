#include "PS_App.hpp"

namespace ps {
	PS_App::PS_App(PS_GameLevel* gameLevel) {
		gameObjects = gameLevel->getGameObjects();
		psPipeline = new PS_Pipeline(&psWindow, &psDevice, &psSwapChain, gameObjects);
	}

	PS_App::~PS_App() {

	}

	void PS_App::mainLoop() {
		while (!glfwWindowShouldClose(psWindow.getWindow())) {
			glfwPollEvents();
			psPipeline->drawFrame();
		}

		vkDeviceWaitIdle(psDevice.device);
	}

	void PS_App::cleanup() {

	}

	void PS_App::run() {
		mainLoop();
		cleanup();
	}
}