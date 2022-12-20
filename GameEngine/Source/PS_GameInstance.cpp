#include "PS_GameInstance.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace ps {
	int PS_GameInstance::startInstance() {
		gameObject1.setModel("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Meshes\\StingSword.obj");
		gameObject1.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\StingSword\\StingSword_Base_Color.png");
		gameObject1.setScale({ 0.1, 0.1, 0.1 });
		gameObject2.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\StingSword\\StingSword_Base_Color.png");
		gameObject3.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\VikingRoom.png");
		gameObject4.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\VikingRoom.png");

		gameObject5.setModel("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Meshes\\Cube.obj");
		gameObject5.setTexture("D:\\VulkanProjects\\PhysicsSimulator\\Content\\Textures\\Basic\\None.png");
		gameObject5.setScale({3, 3, 0.1});
		gameObject5.setLocation({ 0, 0, -10 });

		PS_GameCamera camera;
		camera.setLocation({2, 2, 0});
		camera.setRotation({0.0f, 30.0f, 0.0f});
		//0 3 1
		//0 2.01197 0.154251
		gameLevel.setCamera(&camera);
		gameLevel.addGameObject(&gameObject1);
		gameLevel.addGameObject(&gameObject2);
		gameLevel.addGameObject(&gameObject3);
		gameLevel.addGameObject(&gameObject4);
		gameLevel.addGameObject(&gameObject5);


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