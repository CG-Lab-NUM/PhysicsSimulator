#pragma once
#include "PS_Window.hpp"
#include "PS_Colors.hpp"
#include "PS_Device.hpp"
#include <vector>

namespace ps {
	class PS_Pipeline {
	public:
		PS_Pipeline(PS_Device *psDevice) {
			this->psDevice = psDevice;
		}
		~PS_Pipeline() {
			vkDestroyPipeline(psDevice->getDevice(), graphicsPipeline, nullptr);
			vkDestroyRenderPass(psDevice->getDevice(), renderPass, nullptr);
			vkDestroyPipelineLayout(psDevice->getDevice(), pipelineLayout, nullptr);
			vkDestroyBuffer(psDevice->getDevice(), vertexBuffer, nullptr);
			vkFreeMemory(psDevice->getDevice(), vertexBufferMemory, nullptr);
			vkDestroyImageView(psDevice->getDevice(), textureImageView, nullptr);
			vkDestroySampler(psDevice->getDevice(), textureSampler, nullptr);

		}
		PS_Pipeline(const PS_Pipeline&) = delete;
		PS_Pipeline& operator = (const PS_Pipeline&) = delete;

		void createGraphicsPipeline(PS_Device* psDevice);
		void createRenderPass(VkDevice device, VkFormat swapChainImageFormat);
		static std::vector<char> readFile(const std::string& path);
		void createVertexBuffer(VkPhysicalDevice physicalDevice);
		void createIndexBuffer(PS_Device* psDevice);
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory, VkPhysicalDevice physicalDevice);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		void drawFrame(PS_Window* psWindow, PS_Device* psDevice);
		void createUniformBuffers(PS_Device *psDevice);

		void updateUniformBuffer(uint32_t currentImage, PS_Device* psDevice);

		void createCommandBuffer();
		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, VkRenderPass renderPass, VkPipeline graphicsPipeline, const std::vector<PS_Window::Vertex> vertices);
		void createDescriptorSetLayout(PS_Device* psDevice);
		void createDescriptorPool(PS_Device* psDevice);
		void createDescriptorSets(PS_Device* psDevice);

		void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void createTextureImage();
		void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
		VkCommandBuffer beginSingleTimeCommands();
		void endSingleTimeCommands(VkCommandBuffer commandBuffer);
		void createTextureImageView();
		void createTextureSampler();

		void createDepthResources();
		VkFormat findDepthFormat();
		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		bool hasStencilComponent(VkFormat format) {
			return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
		}

		void LoadModel();
		void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

		template <class T>
		inline void hash_combine(std::size_t& s, const T& v)
		{
			std::hash<T> h;
			s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
		}

		struct S {
			int field1;
			short field2;
			std::string field3;
			// ...
		};


		//
		// Shader
		/*
		const std::vector<PS_Window::Vertex> vertices = {
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

			{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		};

		const std::vector<uint16_t> indices = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};
		*/
		std::vector<PS_Window::Vertex> vertices;
		std::vector<uint32_t> indices;
		const std::string MODEL_PATH = "Meshes/StingSword.obj";
		const std::string TEXTURE_PATH = "Textures/StingSword/StingSword_Base_Color.png";

		//
		// Getters
		//
		VkRenderPass getRenderPass() {
			return renderPass;
		}
		VkPipeline getPipeline() {
			return graphicsPipeline;
		}
		VkBuffer getVertexBuffer() {
			return vertexBuffer;
		}
		const std::vector<PS_Window::Vertex> getVertices() {
			return vertices;
		}
		VkImageView getDepthImageView() {
			return depthImageView;
		}
		uint32_t getMipLevels() {
			return mipLevels;
		}

	private:
		VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);

		VkRenderPass renderPass{};
		VkDescriptorSetLayout descriptorSetLayout;
		VkPipelineLayout pipelineLayout{};
		VkPipeline graphicsPipeline{};
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		VkBuffer indexBuffer{};
		VkDeviceMemory indexBufferMemory{};
		PS_Device *psDevice;
		PS_Colors psColors{};
		PS_Logger psLogger{};

		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		std::vector<void*> uniformBuffersMapped;

		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptorSets;

		VkCommandBuffer commandBuffer;
		std::vector<VkCommandBuffer> commandBuffers;
		bool framebufferResized = false;

		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;

		uint32_t mipLevels;
		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageView textureImageView;
		VkSampler textureSampler;


	};
}