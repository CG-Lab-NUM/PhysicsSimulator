#pragma once

#include "PS_Window.hpp"

namespace ps_window {
	class TestApp {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 800;

		void run();

	private:
		PS_Window psWindow{WIDTH, HEIGHT, "Hello Vulkan"};

	};
}