#include "PS_KeyboardHandler.hpp"

namespace ps {
	std::map<int, bool> PS_KeyboardHandler::currentKeyboard;
	bool PS_KeyboardHandler::lettersEnabled;
	bool PS_KeyboardHandler::numbersEnabled;

	void PS_KeyboardHandler::keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
		letterCallback(window, key, scanCode, action, mods);
		numberCallback(window, key, scanCode, action, mods);

	}

	void PS_KeyboardHandler::letterCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
		//if (!lettersEnabled) {
		//	return;
		//}
		for (int i = 65; i <= 90; i++) {
			if (key == i and action == GLFW_PRESS) {
				currentKeyboard[i] = true;
			}
			else if (key == i and action == GLFW_RELEASE) {
				currentKeyboard[i] = false;
			}
		}
	}

	void PS_KeyboardHandler::numberCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
		//if (!numbersEnabled) {
		//	return;
		//}
		for (int i = 0; i <= 9; i++) {
			if (key == i and action == GLFW_PRESS) {
				currentKeyboard[i] = true;
			}
			else if (key == i and action == GLFW_RELEASE) {
				currentKeyboard[i] = false;
			}
		}
	}

	bool PS_KeyboardHandler::isPressed(char ch) {
		return currentKeyboard[int(ch)];
	}

	// Setters
	void PS_KeyboardHandler::setLetterEnabled(bool enabled) {
		lettersEnabled = enabled;
	}

	void PS_KeyboardHandler::setNumberEnabled(bool enabled) {
		numbersEnabled = enabled;
	}
}