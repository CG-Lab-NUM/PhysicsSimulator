#pragma once
#include "PS_BufferHandler.hpp"
#include "UI_Generic.hpp"

namespace ps {
	class UI_Widget : public PS_Allocator {
	public:
		UI_Widget(PS_Device* device, PS_GameCamera *camera);
		void renderWidget(VkCommandBuffer commandBuffer);

	private:
		void createWidget();
		void createVertexBuffer();
		void createIndexBuffer();
		void translateGeometry();

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::unique_ptr<PS_BufferHandler> vertexBuffer;
		std::unique_ptr<PS_BufferHandler> indexBuffer;

		PS_Device* psDevice;
		PS_GameCamera* gameCamera;
		GeometryObject2D renderComponent;
	};
}