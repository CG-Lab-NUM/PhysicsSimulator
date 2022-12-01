#pragma once
#include "PS_GameGeneric.hpp"

namespace ps {
	class PS_GameObject {
	public:
		PS_GameObject(std::string name) {
			this->name = name;
			this->meshPath = meshPath;
			location = { 0, 0, 0 };
			rotation = { 0, 0, 0 };
			scale = { 1, 1, 1 };
		}
		PS_GameObject(std::string name, std::string meshPath, std::string texturePath) {
			this->name = name;
			this->meshPath = meshPath;
			this->texturePath = texturePath;
			location = { 0, 0, 0 };
			rotation = { 0, 0, 0 };
			scale = { 1, 1, 1 };
		}
		PS_GameObject(std::string name, std::string meshPath, std::string texturePath, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale) {
			this->name = name;
			this->meshPath = meshPath;
			this->texturePath = texturePath;
			this->location = location;
			this->rotation = rotation;
			this->scale = location;
		}

		std::string getName() {
			return name;
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
		
		void setScale(glm::vec3 scale) {
			this->scale = scale;
		}
		void setLocation(glm::vec3 location) {
			this->location = location;
		}

	private:
		std::string name;
		std::string meshPath;
		std::string texturePath;
		glm::vec3 location;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}