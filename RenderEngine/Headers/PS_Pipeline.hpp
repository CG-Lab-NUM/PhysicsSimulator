#pragma once
#include "PS_Helper.hpp"
#include "PS_ModelHandler.hpp"
#include "PS_TextureHandler.hpp"

namespace ps {
	class PS_Pipeline : public PS_Helper {
	public:
		PS_Pipeline(PS_Window *window, PS_Device *device, PS_SwapChain *chain, std::vector<PS_GameObject*> objects, PS_GameCamera* camera);
		~PS_Pipeline();

		void createRenderPass();
		void createDescriptorSetLayout();
		void createGraphicsPipeline();
		VkShaderModule createShaderModule(const std::vector<char>& code);

		void createUniformBuffers();
		void createDescriptorPool();
		void createDescriptorSets();
		
		void createCommandBuffers();
		void createSyncObjects();

		void drawFrame();

		void updateUniformBuffer(uint32_t currentImage);
		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

		int MAX_FRAMES_IN_FLIGHT = 2;

		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		VkDescriptorPool descriptorPool;
		VkDescriptorSetLayout uniformDescriptorSetLayout;
		VkDescriptorSetLayout textureDescriptorSetLayout;

		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;

		std::vector<VkDescriptorSet> descriptorSets;

	private:

		PS_Window* psWindow;
		PS_Device* psDevice;
		PS_SwapChain *psSwapChain;
		PS_GameObject *gameObject;
		PS_GameCamera *gameCamera;

		std::vector<VkCommandBuffer> commandBuffers;

		std::vector<PS_GameObject*> gameObjects;
		std::vector<PS_ModelHandler*> modelLoaders;
		std::vector<PS_TextureHandler*> textureImages;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		uint32_t currentFrame = 0;
	};
}