#include "PS_Test.hpp"
#include <stdexcept>
#include <iostream>

namespace ps {
	PS_Test::PS_Test() {
		createPipelineLayout();
		createPipeline();
		//createCommandBuffers();
	}

	PS_Test::~PS_Test() {
		vkDestroyPipelineLayout(psDevice.device(), pipelineLayout, nullptr);
	}

	void PS_Test::run() {
		while (!psWindow.shouldClose()) {
			glfwPollEvents();
		}
	}

	void PS_Test::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		VkResult result = vkCreatePipelineLayout(psDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout);
		//psDevice.LogResult(result);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout");
		}
	}

	void PS_Test::createPipeline() {
		PipelineConfigInfo pipelineConfig = PS_Pipeline::defaultPipelineConfigInfo(psSwapchain.width(), psSwapchain.height());
		pipelineConfig.renderPass = psSwapchain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;

		if (pipelineConfig.pipelineLayout == VK_NULL_HANDLE) {
			std::cout << "Null Layout";
		}

		if (pipelineConfig.renderPass == VK_NULL_HANDLE) {
			std::cout << "Null Pass";
		}

		psPipeline = std::make_unique<PS_Pipeline>(
			psDevice,
			"Shader/shader.vert.spv",
			"Shader/shader.frag.spv",
			pipelineConfig
		);
	}

	void PS_Test::createCommandBuffers() {

	}
	
	void PS_Test::drawFrame() {

	}
}