#include "PS_Pipeline.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace ps {
	PS_Pipeline::PS_Pipeline(PS_Device& device, const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& config) : psDevice{ device } {
		createGraphicsPipeline(vertFilePath, fragFilePath, config);
	}

	PS_Pipeline::~PS_Pipeline() {

	}

	std::vector<char> PS_Pipeline::readFile(const std::string& filepath) {
		std::ifstream file{filepath, std::ios::ate | std::ios::binary};

		if (!file.is_open()) {
			throw std::runtime_error("Failed to open file : " + filepath);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		file.close();
		return buffer;
	}

	void PS_Pipeline::createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& config) {
		auto vertCode = readFile(vertFilePath);
		auto fragCode = readFile(fragFilePath);

		std::cout << "Vertex Shader Code Size " << vertCode.size() << '\n';
		std::cout << "Fragment Shader Code Size " << fragCode.size() << '\n';
	}

	void PS_Pipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule) {
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(psDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create shader module");
		}
	}

	PipelineConfigInfo PS_Pipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
		PipelineConfigInfo configInfo{};
		return configInfo;
	}
}