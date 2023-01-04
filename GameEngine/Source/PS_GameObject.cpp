#include "PS_GameObject.hpp"

#define NO_MESH "Content/Meshes/Cube.obj"
#define NO_TEXTURE "Content/Textures/Basic/None.png"

namespace ps {
	PS_GameObject::PS_GameObject() {
		setLocation({ 0, 0, 0 });
		setRotation({ 0, 0, 0 });
		setScale({ 1, 1, 1 });
		setModel(NO_MESH);
		setTexture(NO_TEXTURE);
		isBasicShape = false;
	}

	PS_GameObject::PS_GameObject(bool isBasicObject, std::string shape) {
		setLocation({ 0, 0, 0 });
		setRotation({ 0, 0, 0 });
		setScale({ 1, 1, 1 });
		isBasicShape = true;
		makeCube(location, 1);
		setTexture(NO_TEXTURE);
	}

	PS_GameObject::PS_GameObject(glm::vec3 newLocation, glm::vec3 newRotation, glm::vec3 newScale) {
		setLocation(newLocation);
		setRotation(newRotation);
		setScale(newScale);
		setModel(NO_MESH);
		setTexture(NO_TEXTURE);
		isBasicShape = false;
	}

	void PS_GameObject::setLocation(glm::vec3 newLocation) {
		location = newLocation;
	}
	void PS_GameObject::setRotation(glm::vec3 newRotation) {
		rotation = newRotation;
	}
	void PS_GameObject::setScale(glm::vec3 newScale) {
		scale = newScale;
	}
	void PS_GameObject::setModel(std::string newModelPath) {
		modelPath = fileHandler.makeAbsolute(newModelPath);
	}
	void PS_GameObject::setTexture(std::string newTexturePath) {
		texturePath = fileHandler.makeAbsolute(newTexturePath);
	}
	void PS_GameObject::setIsBasicShape(bool newBool, std::vector<Vertex> newVertices) {
		isBasicShape = newBool;
		if (isBasicShape == true) {
			vertices = newVertices;
			return;
		}
		std::vector<Vertex> tempVertices;
		vertices = tempVertices;
	}

	glm::vec3 PS_GameObject::getLocation() {
		return location;
	}
	glm::vec3 PS_GameObject::getRotation() {
		return rotation;
	}
	glm::vec3 PS_GameObject::getScale() {
		return scale;
	}
	std::string PS_GameObject::getModel() {
		return modelPath;
	}
	std::string PS_GameObject::getTexture() {
		return texturePath;
	}
	bool PS_GameObject::getIsBasicShape() {
		return isBasicShape;
	}
	std::vector<Vertex> PS_GameObject::getVertices() {
		return vertices;
	}
	std::string PS_GameObject::getName() {
		return objectName;
	}
	glm::vec3 PS_GameObject::getForwardVector() {
		return forwardVector;
	}
	glm::vec3 PS_GameObject::getRightVector() {
		return rightVector;
	}
	glm::vec3 PS_GameObject::getUpVector() {
		return upVector;
	}
}