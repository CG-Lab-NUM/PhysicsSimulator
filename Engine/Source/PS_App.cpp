#include "PS_App.hpp"

namespace ps {
	PS_App::PS_App() {
		gameObject1.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\VikingRoom.png");
		gameObject2.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\VikingRoom.png");
		gameObject3.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\VikingRoom.png");
		gameObject4.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\VikingRoom.png");
		//gameObjects.push_back(&gameObject);
		gameObjects.push_back(&gameObject1);
		gameObjects.push_back(&gameObject2);
		gameObjects.push_back(&gameObject3);
		gameObjects.push_back(&gameObject4);
		psPipeline = new PS_Pipeline(&psWindow, &psDevice, &psSwapChain, gameObjects, true);
		//psPipeline1 = new PS_Pipeline(&psWindow, &psDevice, &psSwapChain, gameObjects1, false);
	}

	PS_App::~PS_App() {

	}

	void PS_App::mainLoop() {
		while (!glfwWindowShouldClose(psWindow.getWindow())) {
			glfwPollEvents();
			psPipeline->drawFrame();
			//psPipeline1->drawFrame();
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