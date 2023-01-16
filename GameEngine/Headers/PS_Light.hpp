#pragma once
#include "PS_GameObject.hpp"

namespace ps {
	class PS_Light : public PS_GameObject {
	public:
		PS_Light();
		PS_Light(glm::vec3 newLocation, glm::vec3 newRotation, glm::vec3 newScale, glm::vec3 newLightColor);

		void setLightColor(glm::vec3 newColor);
		void setIntensity(float newIntensity);
		glm::vec3 getLightColor();
		float getIntensity();

		bool isDirectional;

	private:
		glm::vec3 lightColor;
		float intensity;
	};
}