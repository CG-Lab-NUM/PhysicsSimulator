#pragma once
#include "PS_Allocator.hpp"

namespace ps {
	class PS_RenderPass {
	public:
		PS_RenderPass(PS_Device *device, PS_SwapChain *swapChain, bool clear);
		VkRenderPass getRenderPass() {
			return renderPass;
		}

	private:
		VkRenderPass renderPass;
		PS_Device *psDevice;
		PS_SwapChain *psSwapChain;
	};
}