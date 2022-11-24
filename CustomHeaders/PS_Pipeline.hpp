#pragma once
#include <PS_Device.hpp>

// std Libraries
#include <string>
#include <vector>

namespace ps {
	struct PipelineConfigInfo {

	};

	class PS_Pipeline {
	public:
		PS_Pipeline(
			PS_Device &device, 
			const std::string& vertFilePath, 
			const std::string& fragFilePath, 
			const PipelineConfigInfo& config);
		~PS_Pipeline();
		PS_Pipeline(const PS_Pipeline&) = delete;
		void operator = (const PS_Pipeline&) = delete;
		static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

	private:
		static std::vector<char> readFile(const std::string& filepath);
		void createGraphicsPipeline(
			const std::string& vertFilePath, 
			const std::string& fragFilePath, 
			const PipelineConfigInfo& config);
		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		PS_Device& psDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};
}