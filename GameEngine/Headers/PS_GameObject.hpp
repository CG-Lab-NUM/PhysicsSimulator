#pragma once
#include "PS_GameGeneric.hpp"
#include "PS_GameMesh.hpp"
#include "PS_FileHandler.hpp"

namespace ps {
	class PS_GameObject : protected PS_GameMesh {
	public:
		PS_GameObject();
		PS_GameObject(bool isBasicObject, std::string shape);
		PS_GameObject(glm::vec3 newLocation, glm::vec3 newRotation, glm::vec3 newScale);

		void setLocation(glm::vec3 newLocation);
		void setRotation(glm::vec3 newRotation);
		void setScale(glm::vec3 newScale);
		void setModel(std::string newModelPath);
		void setTexture(std::string newTexturePath);
		void setName(std::string newName);
		void setIsBasicShape(bool newBool, std::vector<Vertex> newVertices);

		glm::vec3 getLocation();
		glm::vec3 getRotation();
		glm::vec3 getScale();
		glm::vec3 getForwardVector();
		glm::vec3 getRightVector();
		glm::vec3 getUpVector();
		std::string getModel();
		std::string getTexture();
		std::string getName();
		std::vector<Vertex> getVertices();
		bool getIsBasicShape();

	private:
		glm::vec3 location;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::vec3 forwardVector;
		glm::vec3 rightVector;
		glm::vec3 upVector;

		std::string modelPath;
		std::string texturePath;
		std::string objectName;

		bool isBasicShape;
		PS_FileHandler fileHandler;
	};
}