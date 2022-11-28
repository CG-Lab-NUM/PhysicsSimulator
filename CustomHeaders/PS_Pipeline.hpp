#include "PS_Window.hpp"
#include "PS_Colors.hpp"
#include <vector>

namespace ps {
	class PS_Pipeline {
	public:
		PS_Pipeline() {

		}
		~PS_Pipeline() {
			vkDestroyPipeline(device, graphicsPipeline, nullptr);
			vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
			vkDestroyRenderPass(device, renderPass, nullptr);
			vkDestroyBuffer(device, vertexBuffer, nullptr);
			vkFreeMemory(device, vertexBufferMemory, nullptr);
		}
		PS_Pipeline(const PS_Pipeline&) = delete;
		PS_Pipeline& operator = (const PS_Pipeline&) = delete;

		void createGraphicsPipeline(VkDevice device);
		void createRenderPass(VkDevice device, VkFormat swapChainImageFormat);
		static std::vector<char> readFile(const std::string& path);
		void createVertexBuffer(VkPhysicalDevice physicalDevice);

		//
		// Shader
		//
		const std::vector<PS_Window::Vertex> vertices = {
			{{0.0f, -0.5f}, psColors.makeColor("RED")},
			{{0.5f, 0.0f}, psColors.makeColor("RED")},
			{{0.0f, 0.5f}, psColors.makeColor("GREEN")}
		};
		
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

	private:
		VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);

		VkDevice device{};
		VkRenderPass renderPass{};
		VkPipelineLayout pipelineLayout{};
		VkPipeline graphicsPipeline{};
		VkBuffer vertexBuffer{};
		VkDeviceMemory vertexBufferMemory{};

		PS_Colors psColors{};
	};
}