#include "PS_App.hpp"
#include <iostream>

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
		psWindow.createSurface(psDevice.getInstance(), psDevice.getDevice());
		psDevice.setSurface(psWindow.getSurface());
		psDevice.pickPhysicalDevice(psWindow.getSurface());
		psDevice.createLogicalDevice();
		psDevice.createSwapChain(psWindow.getSurface(), psWindow.getWindow());
		psDevice.createImageViews();
		psPipeline.createRenderPass(psDevice.getDevice(), psDevice.getSwapChainImageFormat());
		psPipeline.createGraphicsPipeline(psDevice.getDevice());
		psDevice.createFramebuffers(psPipeline.getRenderPass());
		psDevice.createCommandPool();
		psPipeline.createVertexBuffer(psDevice.getPhysicalDevice());
		psDevice.createCommandBuffer();
		psDevice.createSyncObjects();
	}
	
	void PS_App::mainLoop() {
		while (!glfwWindowShouldClose(psWindow.getWindow())) {
			glfwPollEvents();
			psDevice.drawFrame(psPipeline.getRenderPass(), psPipeline.getPipeline(), psWindow.getWindow(), psPipeline.getVertexBuffer(), psPipeline.getVertices());
		}
		vkDeviceWaitIdle(psDevice.getDevice());
	}

	void PS_App::cleanup() {
		for (auto imageView : psDevice.swapChainImageViews) {
			vkDestroyImageView(psDevice.getDevice(), imageView, nullptr);
		}
	}
}