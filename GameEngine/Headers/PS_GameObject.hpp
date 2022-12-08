#include "PS_GameGeneric.hpp"
#include "PS_GameMesh.hpp"

namespace ps {
	class PS_GameObject : protected PS_GameMesh {
	public:
		PS_GameObject();
		PS_GameObject(bool isBasicObject, std::string shape);
		PS_GameObject(glm::vec3 newLocation, glm::vec3 newRotation, glm::vec3 newScale);

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
		void setIsBasicShape(bool newBool, std::vector<Vertex> newVertices) {
			isBasicShape = newBool;
			if (isBasicShape == true) {
				vertices = newVertices;
				return;
			}
			std::vector<Vertex> tempVertices;
			vertices = tempVertices;
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
		bool getIsBasicShape() {
			return isBasicShape;
		}
		std::vector<Vertex> getVertices() {
			return vertices;
		}

	private:
		glm::vec3 location;
		glm::vec3 rotation;
		glm::vec3 scale;

		std::string modelPath;
		std::string texturePath;

		bool isBasicShape;
	};
}