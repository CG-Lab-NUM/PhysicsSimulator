#include "PS_GameLevel.hpp"

namespace ps {
	PS_GameLevel::PS_GameLevel(std::string path) {
		loadMap(path);
	}

	void PS_GameLevel::loadMap(std::string path) {
		levelPath = path;

		std::ifstream file(path);
		json data = json::parse(file);
		levelName = data["name"];
		for (auto& elem : data["game_objects"]) {
			if (elem["type"] == "EditorCamera") {
				PS_GameCamera *camera = new PS_GameCamera();
				camera->setLocation(get3DVector(elem, "location"));
				camera->setRotation(get3DVector(elem, "rotation"));
				setCamera(camera);
			}
			else if (elem["type"] == "GameObject") {
				PS_GameObject *gameObject = new PS_GameObject();
				gameObject->setLocation(get3DVector(elem, "location"));
				gameObject->setRotation(get3DVector(elem, "rotation"));
				gameObject->setScale(get3DVector(elem, "scale"));
				gameObject->setModel(elem["model_path"]);
				gameObject->setTexture(elem["texture_path"]);
				gameObject->setName(elem["name"]);
				gameObjects.push_back(gameObject);
			}
		}
	}

	glm::vec3 PS_GameLevel::get3DVector(json data, std::string field) {
		glm::vec3 vector;
		vector.x = data[field][0];
		vector.y = data[field][1];
		vector.z = data[field][2];
		return vector;
	}
}