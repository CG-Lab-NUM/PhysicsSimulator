#pragma once
#include "PS_App.hpp"

namespace ps {
	class PS_GameInstance {
	public:
		int startInstance();

	private:
		PS_GameLevel gameLevel{"D:\\VulkanProjects\\PhysicsSimulator\\Content\\Levels\\TestLevel.json"};
		PS_GameObject gameObject;
		PS_GameObject gameObject1{ {0, 1.0f, 0}, {90, 0, 0}, {1, 1, 1} };
		PS_GameObject gameObject2{ {-1.0f, -1.0f, 0}, {0, 0, 0}, {1, 1, 1} };
		PS_GameObject gameObject3{ {0, -1.0f, 0}, {0, 0, 0}, {1, 1, 1} };
		PS_GameObject gameObject4{ {1.0f, -1.0f, 0}, {0, 0, 0}, {1, 1, 1} };
		PS_GameObject gameObject5{ {0, 1.0f, 0}, {90, 0, 0}, {1, 1, 1} };
	};
}