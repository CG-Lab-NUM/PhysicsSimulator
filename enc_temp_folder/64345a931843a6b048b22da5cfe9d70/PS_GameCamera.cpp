#include "PS_GameCamera.hpp"

namespace ps {
	PS_GameCamera::PS_GameCamera() {
		setRotation({ 0.0f, 0.0f, 1.0f });
	}

	glm::vec3 PS_GameCamera::getEye() {
		return getLocation();
	}

	glm::vec3 PS_GameCamera::getCenter() {
		return { 0, 0, 0 };
	}

	glm::vec3 PS_GameCamera::getUp() {
		glm::vec3 upVector = { 0.0f, 0.0f, 1.0f * (0.5f)};
		return upVector;
	}

	void PS_GameCamera::tick() {
		PS_KeyboardHandler::setLetterEnabled(true);
		if (PS_KeyboardHandler::isPressed('W')) {
			setLocation(getLocation() + glm::vec3(0, 0.01, 0));
			std::cout << "Yes";
		}

		if (PS_MouseHandler::isPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			std::cout << PS_MouseHandler::getPosition()[0] << std::endl;
		}
	}
}