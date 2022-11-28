#include "PS_Window.hpp"
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
		}
		PS_Pipeline(const PS_Pipeline&) = delete;
		PS_Pipeline& operator = (const PS_Pipeline&) = delete;

		void createGraphicsPipeline(VkDevice device);
		void createRenderPass(VkDevice device, VkFormat swapChainImageFormat);
		static std::vector<char> readFile(const std::string& path);

		//
		// Getters
		//
		VkRenderPass getRenderPass() {
			return renderPass;
		}
		VkPipeline getPipeline() {
			return graphicsPipeline;
		}

	private:
		VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device);
		VkDevice device{};
		VkRenderPass renderPass{};
		VkPipelineLayout pipelineLayout{};
		VkPipeline graphicsPipeline{};
	};
}