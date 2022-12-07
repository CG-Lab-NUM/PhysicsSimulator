#include "PS_Pipeline.hpp"

namespace ps {
	class PS_UI {
	public:
		PS_UI(PS_Window *psWindow, PS_Device* psDevice, PS_Pipeline *psPipeline);
		~PS_UI();
		//void initImgui();

	private:
		PS_Window* psWindow;
		PS_Device* psDevice;
		PS_Pipeline* psPipeline;
	};
}