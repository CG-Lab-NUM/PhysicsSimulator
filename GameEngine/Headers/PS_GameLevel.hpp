#include "PS_GameGeneric.hpp"
#include "PS_GameObject.hpp"

namespace ps {
	class PS_GameLevel {
	public:
		void loadMap(std::string path) {

		}

		void addGameObject(PS_GameObject* object) {
			gameObjects.push_back(object);
		}

		std::vector<PS_GameObject*> getGameObjects() {
			return gameObjects;
		}
	private:
		std::vector<PS_GameObject*> gameObjects;
	};
}