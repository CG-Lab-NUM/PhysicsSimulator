#include "PS_GameGeneric.hpp"

namespace ps {
	class PS_GameObject {
	public:
		PS_GameObject() {
			setLocation({ 0, 0, 0 });
			setRotation({ 0, 0, 0 });
			setScale({1, 1, 1});
			setModel("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Meshes\\VikingRoom.obj");
			setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\None.png");
		}
		PS_GameObject(glm::vec3 newLocation, glm::vec3 newRotation, glm::vec3 newScale) {
			setLocation(newLocation);
			setRotation(newRotation);
			setScale(newScale);
			setModel("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Meshes\\VikingRoom.obj");
			setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\None.png");
		}

		void setLocation(glm::vec3 newLocation) {
			location = newLocation;
		}
		void setRotation(glm::vec3 newRotation) {
			rotation = newRotation;
		}
		void setScale(glm::vec3 newScale) {
			scale = newScale;
		}
		void setModel(std::string newModelPath) {
			modelPath = newModelPath;
		}
		void setTexture(std::string newTexturePath) {
			texturePath = newTexturePath;
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
		std::string getModel() {
			return modelPath;
		}
		std::string getTexture() {
			return texturePath;
		}

	private:
		glm::vec3 location;
		glm::vec3 rotation;
		glm::vec3 scale;

		std::string modelPath;
		std::string texturePath;
	};
}