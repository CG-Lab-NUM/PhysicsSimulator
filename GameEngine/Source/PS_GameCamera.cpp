#include "PS_GameCamera.hpp"

namespace ps {
	PS_GameCamera::PS_GameCamera() {
		setRotation({ 0.0f, 0.0f, 1.0f });
	}

	glm::vec3 PS_GameCamera::getEye() {
		return getLocation();
	}

	glm::vec3 PS_GameCamera::getCenter() {
		float distance = 1;
		float x = getLocation()[0] + (distance * glm::cos(getRotation()[0]));
		float y = getLocation()[1] + (distance * glm::sin(getRotation()[1]));
		float z = getLocation()[2];
		if (!printed) {
			std::cout << x << " " << y << " " << z << std::endl;
			printed = true;
		}
		return { x, y, z};
	}

	glm::vec3 PS_GameCamera::getUp() {
		//glm::vec3 upVector = {0.0f, 1.0f, getRotation()[2]};
		glm::vec3 upVector = { 0.0f, 0.0f, 1.0f * (0.5f)};
		return upVector;
	}
}