#pragma once
#include "PS_Allocator.hpp"

namespace ps {
	class UI_Screen: public PS_Allocator {
	public:
		UI_Screen(PS_Device* device);

		void render();

	private:

	};
}