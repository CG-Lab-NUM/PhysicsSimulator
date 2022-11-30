#pragma once
#include "PS_Game_Generic.hpp"

namespace ps {
	class PS_GameObject {
	public:
		PS_GameObject(std::string meshPath, std::string texturePath) {
			this->meshPath = meshPath;
			this->texturePath = texturePath;
			location = { 0, 0, 0 };
			rotation = { 0, 0, 0 };
			scale = { 1, 1, 1 };
		}
		PS_GameObject(std::string meshPath, std::string texturePath, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale) {
			this->meshPath = meshPath;
			this->texturePath = texturePath;
			this->location = location;
			this->rotation = rotation;
			this->scale = location;
		}

		std::string getMeshPath() {
			return meshPath;
		}
		std::string getTexturePath() {
			return texturePath;
		}
		glm::vec3 getLocation() {
			return location;
		}
		glm::vec3 getRotation() {
			return rotation;
		}
		glm::vec3 getScale() {
			return scale;
		}


	private:
		std::string meshPath;
		std::string texturePath;
		glm::vec3 location;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}