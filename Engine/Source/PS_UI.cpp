#include "PS_UI.hpp"

namespace ps {
	PS_UI::PS_UI(PS_Window* psWindow, PS_Device *psDevice, PS_Pipeline* psPipeline) {
		this->psWindow = psWindow;
		this->psDevice = psDevice;
		this->psPipeline = psPipeline;
	}

	PS_UI::~PS_UI() {

	}


}