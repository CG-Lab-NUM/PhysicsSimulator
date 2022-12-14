#include "PS_GameObject.hpp"

namespace ps {
	PS_GameObject::PS_GameObject() {
		setLocation({ 0, 0, 0 });
		setRotation({ 0, 0, 0 });
		setScale({ 1, 1, 1 });
		setModel("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Meshes\\Cube.obj");
		setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\None.png");
		isBasicShape = false;
	}

	PS_GameObject::PS_GameObject(bool isBasicObject, std::string shape) {
		setLocation({ 0, 0, 0 });
		setRotation({ 0, 0, 0 });
		setScale({ 1, 1, 1 });
		isBasicShape = true;
		makeCube(location, 1);
		setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\None.png");
	}

	PS_GameObject::PS_GameObject(glm::vec3 newLocation, glm::vec3 newRotation, glm::vec3 newScale) {
		setLocation(newLocation);
		setRotation(newRotation);
		setScale(newScale);
		setModel("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Meshes\\Cube.obj");
		setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\None.png");
		isBasicShape = false;
	}
}