#pragma once
#include "PS_GameGeneric.hpp"
#include "PS_GameCamera.hpp"
#include "PS_Light.hpp"
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

		std::vector<PS_Light*> getLights() {
			return gameLights;
		}

		PS_GameCamera* getCamera() {
			return editorCamera;
		}

	private:
		void switchPipeline();
		void readLights(json elem);
		void readCameras(json elem);
		void readObjects(json elem);
		glm::vec3 read3DVector(json data, std::string field);
		glm::vec4 read4DVector(json data, std::string field);
		PS_Material readMaterial(json elem);
		MaterialComponent readMaterialComponent(json elem);

		std::vector<PS_GameObject*> gameObjects;
		std::vector<PS_Light*> gameLights;
		PS_GameCamera *editorCamera;
		std::string levelPath;
		std::string levelName;
		int currentPipeline;
	};

}