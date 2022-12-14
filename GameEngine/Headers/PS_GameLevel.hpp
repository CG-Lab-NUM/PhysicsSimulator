#pragma once
#include "PS_GameGeneric.hpp"
#include "PS_GameCamera.hpp"

namespace ps {
	class PS_GameLevel {
	public:
		void loadMap(std::string path) {

		}

		void addGameObject(PS_GameObject* object) {
			gameObjects.push_back(object);
		}

		void setCamera(PS_GameCamera *camera) {
			this->camera = camera;
		}

		std::vector<PS_GameObject*> getGameObjects() {
			return gameObjects;
		}

		PS_GameCamera* getCamera() {
			return camera;
		}
	private:
		std::vector<PS_GameObject*> gameObjects;
		PS_GameCamera *camera;
	};
}