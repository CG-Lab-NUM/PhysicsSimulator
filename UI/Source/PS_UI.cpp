#include "PS_UI.hpp"



namespace ps {
	PS_UI::PS_UI(PS_Window* window, PS_Device* device, ImguiInfo pipelineInfo) : PS_Helper(device) {
		psWindow = window;
		psDevice = device;
		this->pipelineInfo = pipelineInfo;

		ImGui::CreateContext();
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui_ImplGlfw_InitForVulkan(psWindow->getWindow(), true);

		ImGui_ImplVulkan_InitInfo info;
		info.DescriptorPool = pipelineInfo.DescriptorPool;
		info.RenderPass = pipelineInfo.RenderPass;
		info.Device = psDevice->device;
		info.PhysicalDevice = psDevice->physicalDevice;
		info.ImageCount = pipelineInfo.ImageCount;
		info.MsaaSamples = psDevice->msaaSamples;
		ImGui_ImplVulkan_Init(&info);

		VkCommandBuffer commandBuffer = beginSingleTimeCommands();
		ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
		endSingleTimeCommands(commandBuffer);

		vkDeviceWaitIdle(psDevice->device);
		ImGui_ImplVulkan_DestroyFontUploadObjects();
	}

	PS_UI::~PS_UI() {
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void PS_UI::createTextureWindow(int gameObjectsSize, std::vector<PS_TextureImage*> textureImages, VkCommandBuffer* commandBuffer) {
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//	ImGui::ShowDemoWindow();
		ImGui::Begin("Window");
		{
			for (int i = 0; i < gameObjectsSize; i++) {
				ImGui::Image(&textureImages[i]->descriptorSet, ImVec2(250, 250));
			}
			//ImGui::Image(&Texture->descriptorSet, ImVec2(300, 300));
			//ImGui::Image(&Texture1->descriptorSet, ImVec2(300, 300));
			//ImGui::Image(&Texture2->descriptorSet, ImVec2(300, 300));
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), *commandBuffer, 0, NULL);
	}
}