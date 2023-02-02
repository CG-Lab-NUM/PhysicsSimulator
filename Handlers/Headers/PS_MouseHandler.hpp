#pragma once
#include "PS_RenderGeneric.hpp"

namespace ps {
	class PS_MouseHandler {
	public:
		static void positionCallback(GLFWwindow* window, double xpos, double ypos);
		static void enterCallback(GLFWwindow* window, int entered);
		static void buttonCallback(GLFWwindow* window, int button, int action, int mods);

		static bool isPressed(int button);
		static glm::vec2 getPosition() {
			return glm::vec2(xPos, yPos);
		}
	private:
		static double xPos;
		static double yPos;
		static std::map<int, bool> pressed;

		static void basicButtonCallback(int button, int action, int mods);
	};
}