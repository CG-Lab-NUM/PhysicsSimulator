#include "PS_App.hpp"
#include <iostream>

namespace ps {
	PS_App::PS_App() {
		psDevice.createInstance();
		psDevice.setupDebugMessenger();
		psWindow.createSurface(psDevice.getInstance(), psDevice.getDevice());
		psDevice.setSurface(psWindow.getSurface());
		psDevice.pickPhysicalDevice(psWindow.getSurface());
		psDevice.createLogicalDevice();
		psDevice.createSwapChain(&psWindow);
		psDevice.createImageViews(psPipeline.getMipLevels());
		psPipeline.createRenderPass();
		psPipeline.createDescriptorSetLayout();
		psPipeline.createGraphicsPipeline();
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
		psPipeline.createVertexBuffer();
		psPipeline.createIndexBuffer();
		psPipeline.createUniformBuffers();
		psPipeline.createDescriptorPool();
		psPipeline.createDescriptorSets();
		psPipeline.createCommandBuffer();
		psDevice.createSyncObjects();
	}

	void PS_App::run() {
		mainLoop();
	}
	
	void PS_App::mainLoop() {
		while (!glfwWindowShouldClose(psWindow.getWindow())) {
			glfwPollEvents();
			psPipeline.drawFrame(&psWindow);
		}
		vkDeviceWaitIdle(psDevice.getDevice());
	}
}