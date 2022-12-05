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
		PS_GameObject building1{ "viking", "D:\\VulkanProjects\\PhysicsSimulator\\Content\\Meshes\\VikingRoom.obj", "D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\VikingRoom.png" };
		building1.setScale({0.25, 0.25, 0.25});

		PS_GameObject building2{ "viking2", "D:\\VulkanProjects\\PhysicsSimulator\\Content\\Meshes\\VikingRoom.obj", "D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\VikingRoom.png" };
		building2.setScale({ 0.25, 0.25, 0.25 });
		building2.setLocation({ 0, 1.5, 0});

		PS_GameLevel level;
		level.addGameObject(&building1);
		level.addGameObject(&building2);

		psDevice.createFramebuffers(psPipeline.getRenderPass(), psPipeline.getDepthImageView(), psPipeline.getColorImageView());
		psPipeline.createTextureImage(&building1);
		psPipeline.createTextureImageView();
		psPipeline.createTextureSampler();
		//psPipeline.loadModel(&viking);
		psPipeline.loadLevel(&level);
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