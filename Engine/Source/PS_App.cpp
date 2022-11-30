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
		psDevice.createSwapChain(&psWindow);
		psDevice.createImageViews(psPipeline.getMipLevels());
		psPipeline.createRenderPass(psDevice.getDevice(), psDevice.getSwapChainImageFormat());
		psPipeline.createDescriptorSetLayout(&psDevice);
		psPipeline.createGraphicsPipeline(&psDevice);
		psDevice.createCommandPool();
		psPipeline.createColorResources();
		psPipeline.createDepthResources();
		PS_GameObject viking{ "D:\\VulkanProjects\\PhysicsSimulator\\Meshes\\VikingRoom.obj", "D:\\VulkanProjects\\PhysicsSimulator\\Textures\\Basic\\VikingRoom.png" };
		PS_GameObject sword{ "D:\\VulkanProjects\\PhysicsSimulator\\Meshes\\StingSword.obj", "D:\\VulkanProjects\\PhysicsSimulator\\Textures\\StingSword\\StingSword_BasicColor.png" };
		psDevice.createFramebuffers(psPipeline.getRenderPass(), psPipeline.getDepthImageView(), psPipeline.getColorImageView());
		psPipeline.createTextureImage(&viking);
		psPipeline.createTextureImageView();
		psPipeline.createTextureSampler();
		psPipeline.loadModel(&viking);
		//psPipeline.loadModel(&sword);
		//psPipeline.loadModel(psLoader.meshPaths[1], psLoader.materialPaths[0]);
		//psPipeline.loadModel(psLoader.meshPaths[0], psLoader.materialPaths[0]);
		psPipeline.createVertexBuffer(psDevice.getPhysicalDevice());
		psPipeline.createIndexBuffer(&psDevice);
		psPipeline.createUniformBuffers(&psDevice);
		psPipeline.createDescriptorPool(&psDevice);
		psPipeline.createDescriptorSets(&psDevice);
		psPipeline.createCommandBuffer();
		psDevice.createSyncObjects();
	}
	
	void PS_App::mainLoop() {
		while (!glfwWindowShouldClose(psWindow.getWindow())) {
			glfwPollEvents();
			psPipeline.drawFrame(&psWindow, &psDevice);
		}
		vkDeviceWaitIdle(psDevice.getDevice());
	}
	void PS_App::cleanup() {

	}
}