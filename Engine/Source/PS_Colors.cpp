#include "PS_Colors.hpp"

namespace ps {
	glm::vec3 PS_Colors::makeColor(std::string color) {
		if (color == "RED") {
			return { 1.0f, 0.0f, 0.0f };
		}
		else if (color == "GREEN") {
			return { 0.0f, 1.0f, 0.0f };
		}
		else if (color == "BLUE") {
			return { 0.0f, 0.0f, 1.0f };
		}
		else {
			return { 0.0f, 0.0f, 0.0f };
		}
	}
}