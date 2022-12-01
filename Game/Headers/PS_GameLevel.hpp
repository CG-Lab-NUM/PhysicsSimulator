#pragma once
#include "PS_GameGeneric.hpp"
#include "PS_GameObject.hpp"

namespace ps {
	class PS_GameLevel {
	public:
		PS_GameLevel() {
			PS_GameObject object{"MapObject"};
		}

		void addGameObject(PS_GameObject *gameObject) {
			gameObjects.push_back(gameObject);
		}

		void loadMap() {

		}

		// Getters
		std::vector<PS_GameObject*> getGameObjects() {
			return gameObjects;
		}
		PS_GameObject *getObjectByIndex(int index) {
			return gameObjects[index];
		}
		PS_GameObject *getObjectByName(std::string name) {
			return gameObjects[0];
		}
	private:
		std::vector<PS_GameObject*> gameObjects;
	};
}