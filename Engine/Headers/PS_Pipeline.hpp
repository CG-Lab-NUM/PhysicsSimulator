#pragma once
#include "PS_Helper.hpp"

namespace ps {
	class PS_Pipeline : public PS_Helper {
	public:
		PS_Pipeline(PS_Window *window, PS_Device *device, PS_SwapChain *chain);
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

		void initImgui();
		

		const int MAX_FRAMES_IN_FLIGHT = 2;

		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		VkDescriptorPool descriptorPool;
		VkDescriptorSetLayout uniformDescriptorSetLayout;
		VkDescriptorSetLayout textureDescriptorSetLayout;

		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;

		std::vector<VkDescriptorSet> descriptorSets;
		TextureImage *Texture;
		TextureImage *Texture1;

	private:

		const std::string MODEL_PATH = "D:\\VulkanProjects\\PhysicsSimulator\\Content\\Meshes/VikingRoom.obj";
		const std::string TEXTURE_PATH = "D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures/Basic/VikingRoom.png";

		PS_Window* psWindow;
		PS_Device* psDevice;
		PS_SwapChain* psSwapChain;

		std::vector<VkCommandBuffer> commandBuffers;

		ModelLoader *Model;
		ModelLoader *Model1;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		uint32_t currentFrame = 0;
	};
}