#pragma once
#include "PS_BufferHandler.hpp"
#include "UI_Generic.hpp"
#include "PS_MouseHandler.hpp"
#include "PS_ColorHandler.hpp"


namespace ps {
	class UI_Widget : public PS_Allocator {
	public:
		UI_Widget(PS_Device* device, PS_GameCamera *camera, PS_Window *window);
		void renderWidget(VkCommandBuffer commandBuffer);

	private:
		void createWidget();
		void createVertexBuffer();
		void createIndexBuffer();
		void translateGeometry();
		void onClick();
		glm::vec3 translateCoord(glm::vec2 pos);
		
		void printVector(std::string label, glm::vec3 pos);

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::unique_ptr<PS_BufferHandler> vertexBuffer;
		std::unique_ptr<PS_BufferHandler> indexBuffer;
		glm::vec3 windowCenter;
		glm::vec3 xWindow, yWindow, zWindow;
		glm::vec3 normal;
		float width, height;

		PS_Device* psDevice;
		PS_GameCamera* gameCamera;
		PS_Window* psWindow;
		GeometryObject2D renderComponent;
	};
}