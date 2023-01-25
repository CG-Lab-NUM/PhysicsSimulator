#include "PS_GameObject.hpp"

#define NO_MESH "Content/Meshes/Cube.obj"

namespace ps {
	PS_GameObject::PS_GameObject() {
		setLocation({ 0, 0, 0 });
		setRotation({ 0, 0, 0 });
		setScale({ 1, 1, 1 });
		setModel(NO_MESH);
		isBasicShape = false;
	}

	PS_GameObject::PS_GameObject(glm::vec3 newLocation, glm::vec3 newRotation, glm::vec3 newScale) {
		setLocation(newLocation);
		setRotation(newRotation);
		setScale(newScale);
		setModel(NO_MESH);
		isBasicShape = false;
	}

	PS_GameObject::PS_GameObject(glm::vec3 newLocation, glm::vec3 newRotation, glm::vec3 newScale, GeometryObject3D shape) : PS_GameMesh{ shape } {
		setLocation(newLocation);
		setRotation(newRotation);
		setScale(newScale);
		setModel(NO_MESH);
		isBasicShape = true;
	}

	PS_GameObject::PS_GameObject(GeometryObject3D shape) : PS_GameMesh{ shape }  {
		isBasicShape = true;
	}

	void PS_GameObject::tick() {

	}

	void PS_GameObject::setLocation(glm::vec3 newLocation) {
		location = newLocation;
	}
	void PS_GameObject::setRotation(glm::vec3 newRotation) {
		rotation = newRotation;
		forwardVector = glm::vec3(
			glm::cos(rotation.x) * glm::sin(rotation.y),
			glm::cos(rotation.x) * glm::cos(rotation.y),
			-glm::sin(rotation.x)
		);
		rightVector = -glm::vec3(
			glm::cos(rotation.y),
			-glm::sin(rotation.y),
			0
		);
		upVector = glm::cross(forwardVector, rightVector);
	}
	void PS_GameObject::setScale(glm::vec3 newScale) {
		scale = newScale;
	}
	void PS_GameObject::setMeshRotation(glm::vec3 newRotation) {
		meshRotation = newRotation;
	}
	void PS_GameObject::setModel(std::string newModelPath) {
		modelPath = PS_FileHandler::makeAbsolute(newModelPath);
	}
	void PS_GameObject::setMaterial(PS_Material newMaterial) {
		material = newMaterial;
	}
	void PS_GameObject::setName(std::string newName) {
		objectName = newName;
	}
	void PS_GameObject::setAlpha(float newAlpha) {
		alpha = newAlpha;
	}
	void PS_GameObject::setGeometryObject(GeometryObject3D shape) {
		isBasicShape = true;
		setMeshGeometryObject(shape);
	}

	glm::vec3 PS_GameObject::getLocation() {
		return location;
	}
	glm::vec3 PS_GameObject::getRotation() {
		return rotation;
	}
	glm::vec3 PS_GameObject::getMeshRotation() {
		return meshRotation;
	}
	glm::vec3 PS_GameObject::getScale() {
		return scale;
	}
	std::string PS_GameObject::getModel() {
		return modelPath;
	}
	PS_Material PS_GameObject::getMaterial() {
		return material;
	}
	bool PS_GameObject::getIsBasicShape() {
		return isBasicShape;
	}
	float PS_GameObject::getAlpha() {
		return alpha;
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
	GeometryObject3D PS_GameObject::getGeometryObject() {
		return getMeshGeometryObject();
	}
}