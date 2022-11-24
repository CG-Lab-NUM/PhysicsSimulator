#include "TestApp.hpp"

namespace ps_window {
	void TestApp::run() {
		while (!psWindow.shouldClose()) {
			glfwPollEvents();
		}
	}
}