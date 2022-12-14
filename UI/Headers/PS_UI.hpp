#pragma once
#include "PS_Helper.hpp"
#include "PS_TextureImage.hpp"
#include "PS_ModelLoader.hpp"

#ifndef IMGUI_H
#define IMGUI_H
#include <imconfig.h>
#include <imgui_tables.cpp>
#include <imgui_internal.h>
#include <imgui.cpp>
#include <imgui_draw.cpp>
#include <imgui_widgets.cpp>
#include <imgui_demo.cpp>
#include <backends/imgui_impl_glfw.cpp>
#include <backends/imgui_impl_vulkan_but_better.h>
#endif

namespace ps {
	class PS_UI : PS_Helper {
	public:
		PS_UI(PS_Window* psWindow, PS_Device* psDevice, ImguiInfo pipelineInfo);
		~PS_UI();
		void createTextureWindow(int gameObjectsSize, std::vector<PS_TextureImage*> textureImages, VkCommandBuffer* commandBuffer);

	private:
		PS_Window *psWindow;
		PS_Device *psDevice;
		ImguiInfo pipelineInfo;
	};
}