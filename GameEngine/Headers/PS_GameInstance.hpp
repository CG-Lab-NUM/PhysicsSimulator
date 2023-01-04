#pragma once
#include "PS_App.hpp"

namespace ps {
	class PS_GameInstance {
	public:
		int startInstance();

	private:
		PS_GameLevel gameLevel{"D:\\VulkanProjects\\PhysicsSimulator\\Content\\Levels\\TestLevel.json"};
	};
}