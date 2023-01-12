#include "PS_Shader.hpp"

namespace ps {
	PS_Shader::PS_Shader(PS_Device *device, std::string path, int type) {
		psDevice = device;
		const std::vector<char>& shaderCode = PS_FileHandler::readFile(path);
		createShaderModule(shaderCode);
		switch (type) {
		case 1:
			createVertexShader();
			break;
		case 2:
			createFragmentShader();
			break;
		default:
			break;
		}
	}

	void PS_Shader::createShaderModule(const std::vector<char>& code) {
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
		if (vkCreateShaderModule(psDevice->device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
			throw std::runtime_error("failed to create shader module!");
		}
	}

	void PS_Shader::createVertexShader() {
		shaderCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderCreateInfo.module = shaderModule;
		shaderCreateInfo.pName = "main";
	}

	void PS_Shader::createFragmentShader() {
		shaderCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		shaderCreateInfo.module = shaderModule;
		shaderCreateInfo.pName = "main";
	}

	void PS_Shader::destroy() {
		vkDestroyShaderModule(psDevice->device, shaderModule, nullptr);
	}
}