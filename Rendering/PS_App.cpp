#include <iostream>
#include "PS_App.hpp"

namespace ps {
	PS_App::PS_App() {

	}

	PS_App::~PS_App() {
		cleanup();
	}


	void PS_App::run() {
		initVulkan();
		mainLoop();
		cleanup();
	}

	void PS_App::initVulkan() {
		psDevice.createInstance();
		psDevice.setupDebugMessenger();
		psDevice.pickPhysicalDevice();
		psDevice.createLogicalDevice();
	}

	void PS_App::mainLoop() {
		while (!glfwWindowShouldClose(psWindow.getWindow())) {
			glfwPollEvents();
		}
	}

	void PS_App::cleanup() {

	}
}