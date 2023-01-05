#include "PS_MouseHandler.hpp"

namespace ps {
	double PS_MouseHandler::xPos;
	double PS_MouseHandler::yPos;
	std::map<int, bool> PS_MouseHandler::pressed;

	void PS_MouseHandler::positionCallback(GLFWwindow* window, double xpos, double ypos) {
		xPos = xpos;
		yPos = ypos;
	}

	void PS_MouseHandler::enterCallback(GLFWwindow* window, int entered) {

	}

	void PS_MouseHandler::buttonCallback(GLFWwindow* window, int button, int action, int mods) {
		basicButtonCallback(button, action, mods);
	}

	void PS_MouseHandler::basicButtonCallback(int button, int action, int mods) {
		for (int i = 0; i <= 2; i++) {
			if (button == i && action == GLFW_PRESS) {
				pressed[i] = true;
			}
			else if (button == i && action == GLFW_RELEASE) {
				pressed[i] = false;
			}
		}
	}

	bool PS_MouseHandler::isPressed(int button) {
		return pressed[button];
	}
}