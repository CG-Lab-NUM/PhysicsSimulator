#include "PS_Pipeline.hpp"
#include <chrono>
#include <numeric>
#include <memory>

namespace ps {
	PS_Pipeline::PS_Pipeline(
		PS_Window* window, 
		PS_Device *device, 
		PS_SwapChain *chain, 
		std::vector<PS_GameObject*> objects,
		PS_GameCamera *camera,
		std::string vertexShader,
		std::string fragmentShader) : PS_Allocator(device) {
		
		psWindow = window;
		psDevice = device;
		psSwapChain = chain;
		gameObjects = objects;
		gameCamera = camera;
		vertexShaderPath = vertexShader;
		fragmentShaderPath = fragmentShader;
		psRenderPass = new PS_RenderPass(psDevice, psSwapChain);
		uiRenderPass = new PS_RenderPass(psDevice, psSwapChain);
		psDescriptorSets = new PS_DescriptorSet(psDevice, MAX_FRAMES_IN_FLIGHT, static_cast<uint32_t>(gameObjects.size()));
		psDescriptorSets->createLayout({
			0,
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			1,
			VK_SHADER_STAGE_VERTEX_BIT,
			nullptr
		});
		psDescriptorSets->createLayout({
			0,
			VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			1,
			VK_SHADER_STAGE_FRAGMENT_BIT,
			nullptr
		});
		createGraphicsPipeline();
		psDevice->createCommandPool();
		psSwapChain->createColorResources();
		psSwapChain->createDepthResources();
		psSwapChain->createFramebuffers(psRenderPass->getRenderPass());
		createUniformBuffers();
		psDescriptorSets->createPool();
		psDescriptorSets->createSets(&uniformBuffers);
		widget = new UI_Widget(psDevice, gameCamera);
		loadGameObjects();
		createCommandBuffers();
		createSyncObjects();
	}

	void PS_Pipeline::createGraphicsPipeline() {
		// Shader
		PS_Shader vertShader{ psDevice, vertexShaderPath, VERTEX_SHADER };
		PS_Shader fragShader{ psDevice, fragmentShaderPath, FRAGMENT_SHADER };
		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShader.getShaderCreateInfo(), fragShader.getShaderCreateInfo()};

		// Vertex
		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		auto bindingDescription = Vertex::getBindingDescription();
		auto attributeDescriptions = Vertex::getAttributeDescriptions();
		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;
		
		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.scissorCount = 1;

		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = psDevice->msaaSamples;

		VkPipelineDepthStencilStateCreateInfo depthStencil{};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.depthTestEnable = VK_TRUE;
		depthStencil.depthWriteEnable = VK_TRUE;
		depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
		depthStencil.depthBoundsTestEnable = VK_FALSE;
		depthStencil.stencilTestEnable = VK_FALSE;

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		std::vector<VkDynamicState> dynamicStates = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};
		VkPipelineDynamicStateCreateInfo dynamicState{};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
		dynamicState.pDynamicStates = dynamicStates.data();

		VkPushConstantRange psRange;
		psRange.offset = 0;
		psRange.size = sizeof(PushConstant);
		psRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		VkDescriptorSetLayout setLayouts[] = {
			psDescriptorSets->getSetLayout(0), 
			psDescriptorSets->getSetLayout(1) 
		};

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 2;
		pipelineLayoutInfo.pSetLayouts = setLayouts;
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &psRange;

		if (vkCreatePipelineLayout(psDevice->device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout!");
		}

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &dynamicState;
		pipelineInfo.layout = pipelineLayout;
		pipelineInfo.renderPass = psRenderPass->getRenderPass();
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(psDevice->device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
			throw std::runtime_error("failed to create graphics pipeline!");
		}

		vertShader.destroy();
		fragShader.destroy();
	}
	void PS_Pipeline::createUniformBuffers() {
		VkDeviceSize bufferSize = sizeof(UniformBufferObject);
		uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			uniformBuffers[i] = std::make_unique<PS_BufferHandler>(
				psDevice,
				sizeof(UniformBufferObject),
				1,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
			);
		}
	}
	void PS_Pipeline::updateUniformBuffer(uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		pointLight.setLocation({5, -8, 0});
		pointLight.setLightColor({1, 0, 0});

		UniformBufferObject ubo{};
		glm::highp_mat4 model = glm::mat4(1.0f);
		glm::highp_mat4 view = glm::lookAt(gameCamera->getEye(), gameCamera->getCenter(), gameCamera->getUp());
		glm::highp_mat4 proj = glm::perspective(glm::radians(45.0f), psSwapChain->swapChainExtent.width / (float)psSwapChain->swapChainExtent.height, 1.0f, 100.0f);
		proj[1][1] *= -1;
		ubo.transform = proj * view * model;
		ubo.lightColor = glm::vec4(pointLight.getLightColor(), 1);
		ubo.lightPosition = pointLight.getLocation();
		ubo.ambientLightColor = glm::vec4(1, 1, 1, 1);

		PS_BufferHandler uniformBuffer{
			psDevice,
			sizeof(ubo),
			1,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		};
		uniformBuffer.map();
		uniformBuffer.writeToBuffer((void*)&ubo);
		copyBuffer(uniformBuffer.getBuffer(), uniformBuffers[currentImage]->getBuffer(), sizeof(UniformBufferObject));
	}

	void PS_Pipeline::drawFrame() {
		uint32_t imageIndex;
		VkResult result;
		VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
		VkSubmitInfo submitInfo{
			VK_STRUCTURE_TYPE_SUBMIT_INFO,
			nullptr,
			1, waitSemaphores, waitStages,
			1, &commandBuffers[currentFrame],
			1, signalSemaphores
		};
		vkWaitForFences(psDevice->device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
		result = vkAcquireNextImageKHR(psDevice->device, psSwapChain->swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			psSwapChain->recreateSwapChain(psRenderPass->getRenderPass());
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}
		updateUniformBuffer(currentFrame);
		recordCommandBuffer(commandBuffers[currentFrame], imageIndex);
		vkResetFences(psDevice->device, 1, &inFlightFences[currentFrame]);


		if (vkQueueSubmit(psDevice->graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		VkSwapchainKHR swapChains[] = { psSwapChain->swapChain };
		VkPresentInfoKHR presentInfo{
			VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
			nullptr,
			1, signalSemaphores,
			1, swapChains,
			&imageIndex,
			&result
		};

		result = vkQueuePresentKHR(psDevice->presentQueue, &presentInfo);
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || psWindow->framebufferResized) {
			psWindow->framebufferResized = false;
			psSwapChain->recreateSwapChain(psRenderPass->getRenderPass());
		}
		else if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to present swap chain image!");
		}

		currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}
	void PS_Pipeline::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}
		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { {0.0f, 0.0f, 0.0f, 0.5f} };
		clearValues[1].depthStencil = { 1.0f, 0 };

		VkRenderPassBeginInfo renderPassInfo{
			VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
			nullptr,
			psRenderPass->getRenderPass(),
			psSwapChain->swapChainFramebuffers[imageIndex],
			{{0,0}, psSwapChain->swapChainExtent},
			static_cast<uint32_t>(clearValues.size()),
			clearValues.data()
		};

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
		createViewport(commandBuffer);
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, psDescriptorSets->getSetReference(currentFrame), 0, nullptr);
		
		renderGameObjects(commandBuffer);

		widget->renderWidget(commandBuffer);

		vkCmdEndRenderPass(commandBuffer);
		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}
	void PS_Pipeline::createCommandBuffers() {
		commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = psDevice->commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

		if (vkAllocateCommandBuffers(psDevice->device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}
	}
	void PS_Pipeline::createSyncObjects() {
		imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			if (vkCreateSemaphore(psDevice->device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(psDevice->device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(psDevice->device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
	}
	void PS_Pipeline::createViewport(VkCommandBuffer commandBuffer) {
		VkViewport viewport{
			0.0f, // x
			0.0f, // y
			(float)psSwapChain->swapChainExtent.width,
			(float)psSwapChain->swapChainExtent.height,
			0.0f, // Min Depth
			1.0f // Max Depth
		};
		VkRect2D scissor{
			{0, 0}, // Offset
			psSwapChain->swapChainExtent // Extent
		};
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
	}
	void PS_Pipeline::loadGameObjects() {
		for (int i = 0; i < gameObjects.size(); i++) {
			PS_ModelHandler* Model = new PS_ModelHandler(psDevice);
			modelLoaders.push_back(Model);
			Model->Load(gameObjects[i]);

			PS_TextureHandler* Texture = new PS_TextureHandler(psDevice, psDescriptorSets->getPoolReference(), psDescriptorSets->getSetLayoutReference(1));
			textureImages.push_back(Texture);
			textureImages[i]->Load(gameObjects[i]);
		}
	}
	void PS_Pipeline::renderGameObjects(VkCommandBuffer commandBuffer) {
		PushConstant pushConstant;
		for (int i = 0; i < gameObjects.size(); i++) {
			vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &textureImages[i]->descriptorSet, 0, nullptr);
			vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(pushConstant), &pushConstant);
			modelLoaders[i]->Render(commandBuffer);
		}
	}
}