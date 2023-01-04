#pragma once
#include "PS_GameObject.hpp"
#include "PS_Window.hpp"

namespace ps {
	class PS_GameCamera : public PS_GameObject {
	public:
		PS_GameCamera();
		glm::vec3 getEye();
		glm::vec3 getCenter();
		glm::vec3 getUp();

		void tick();
	private:
		bool mouseRightStatus = false;
		glm::vec2 previousCursorPosition;
		glm::vec2 currentCursorPosition;
		
		void keyboardMovement();
		void mouseRotation();
		float makeAbsolute(float num);
	};
}