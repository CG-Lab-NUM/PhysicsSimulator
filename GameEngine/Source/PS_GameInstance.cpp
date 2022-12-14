#include "PS_GameInstance.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace ps {
	int PS_GameInstance::startInstance() {
		/*
		gameObject1.setModel("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Meshes\\StingSword.obj");
		gameObject1.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\StingSword\\StingSword_Base_Color.png");
		gameObject1.setScale({ 0.1, 0.1, 0.1 });
		gameObject2.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\StingSword\\StingSword_Base_Color.png");
		gameObject3.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\VikingRoom.png");
		gameObject4.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\VikingRoom.png");

		gameLevel.addGameObject(&gameObject1);
		gameLevel.addGameObject(&gameObject2);
		gameLevel.addGameObject(&gameObject3);
		gameLevel.addGameObject(&gameObject4);
		gameLevel.addGameObject(&gameObject5);
		*/

		ps::PS_App app{ &gameLevel };
		try {
			app.run();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
}