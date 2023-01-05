#include "PS_GameCamera.hpp"

#define ROTATION_SENSITIVITY 0.01f
#define MOVEMENT_SPEED 0.01f

namespace ps {
	PS_GameCamera::PS_GameCamera() {
		setRotation({ 0.0f, 0.0f, 1.0f });
	}

	glm::vec3 PS_GameCamera::getEye() {
		return getLocation();
	}

	glm::vec3 PS_GameCamera::getCenter() {
		return getLocation() + getForwardVector();
	}

	glm::vec3 PS_GameCamera::getUp() {
		return getUpVector();
	}

	void PS_GameCamera::tick() {
		keyboardMovement();
		mouseRotation();
	}

	void PS_GameCamera::keyboardMovement() {
		PS_KeyboardHandler::setLetterEnabled(true);
		if (PS_KeyboardHandler::isPressed('W')) {
			setLocation(getLocation() + (getForwardVector() * MOVEMENT_SPEED));
		}
		if (PS_KeyboardHandler::isPressed('S')) {
			setLocation(getLocation() - (getForwardVector() * MOVEMENT_SPEED));
		}
		if (PS_KeyboardHandler::isPressed('A')) {
			setLocation(getLocation() + (getRightVector() * MOVEMENT_SPEED));
		}
		if (PS_KeyboardHandler::isPressed('D')) {
			setLocation(getLocation() - (getRightVector() * MOVEMENT_SPEED));
		}
	}

	void PS_GameCamera::mouseRotation() {
		if (PS_MouseHandler::isPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			currentCursorPosition = PS_MouseHandler::getPosition();
			if (previousCursorPosition != currentCursorPosition) {
				glm::vec3 tempRotation = getRotation();

				if (currentCursorPosition.x > previousCursorPosition.x) {
					tempRotation.y += ROTATION_SENSITIVITY;
				}
				else if (currentCursorPosition.x < previousCursorPosition.x) {
					tempRotation.y -= ROTATION_SENSITIVITY;
				}

				if (currentCursorPosition.y > previousCursorPosition.y) {
					tempRotation.x += ROTATION_SENSITIVITY;
				}
				else if (currentCursorPosition.y < previousCursorPosition.y) {
					tempRotation.x -= ROTATION_SENSITIVITY;
				}
				setRotation(tempRotation);
			}
		}
		previousCursorPosition = currentCursorPosition;
	}

	float PS_GameCamera::makeAbsolute(float num) {
		if (num < 0) {
			return num * -1;
		}
		return num;
	}
}