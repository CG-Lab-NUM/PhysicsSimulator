#pragma once
#include "PS_GameGeneric.hpp"
#include "PS_GameCamera.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define UNLIT_PIPELINE 1
#define LIT_PIPELINE 2

namespace ps {
	class PS_GameLevel {
	public:
		PS_GameLevel(std::string path);
		void tick();
		void loadMap(std::string path);
		glm::vec3 get3DVector(json data, std::string field);

		void addGameObject(PS_GameObject* object) {
			gameObjects.push_back(object);
		}

		void setCamera(PS_GameCamera *camera) {
			editorCamera = camera;
		}

		int getPipeline() {
			return currentPipeline;
		}

		std::vector<PS_GameObject*> getGameObjects() {
			return gameObjects;
		}

		PS_GameCamera* getCamera() {
			return editorCamera;
		}
	private:
		void switchPipeline();

		std::vector<PS_GameObject*> gameObjects;
		PS_GameCamera *editorCamera;
		std::string levelPath;
		std::string levelName;
		int currentPipeline;
	};
}