#pragma once
#include "PS_Allocator.hpp"
#define VERTEX_SHADER 1
#define FRAGMENT_SHADER 2

namespace ps {
	class PS_Shader {
	public:
		PS_Shader(PS_Device *device, std::string path, int type);
		void destroy();
		VkPipelineShaderStageCreateInfo getShaderCreateInfo() {
			return shaderCreateInfo;
		}
	private:
		void createShaderModule(const std::vector<char>& code);
		void createVertexShader();
		void createFragmentShader();

		PS_Device *psDevice;
		VkShaderModule shaderModule;
		VkPipelineShaderStageCreateInfo shaderCreateInfo;
	};
}