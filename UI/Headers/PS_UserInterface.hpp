#pragma once
#include "PS_Helper.hpp"
#include "PS_TextureImage.hpp"
#include "PS_ModelLoader.hpp"

namespace ps {
	class PS_UserInterface : PS_Helper {
	public:
		PS_UserInterface(PS_Window* psWindow, PS_Device* psDevice, ImguiInfo pipelineInfo);
		~PS_UserInterface();
		void createTextureWindow(int gameObjectsSize, std::vector<PS_TextureImage*> textureImages, VkCommandBuffer* commandBuffer);

	private:
		PS_Window *psWindow;
		PS_Device *psDevice;
		ImguiInfo pipelineInfo;
	};
}