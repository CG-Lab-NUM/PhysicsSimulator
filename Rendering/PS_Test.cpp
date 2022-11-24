#include "PS_Test.hpp"

namespace ps {
	void PS_Test::run() {
		while (!psWindow.shouldClose()) {
			glfwPollEvents();
		}
	}
}