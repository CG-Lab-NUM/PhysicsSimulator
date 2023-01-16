#include "PS_Light.hpp"

namespace ps {
	PS_Light::PS_Light() : PS_GameObject{} {
		lightColor = glm::vec3(1);
		setModel("Content/Meshes/Sphere.obj");
	}
	PS_Light::PS_Light(
		glm::vec3 newLocation,
		glm::vec3 newRotation,
		glm::vec3 newScale,
		glm::vec3 newLightColor) : PS_GameObject{ newLocation, newRotation, newScale } {
		lightColor = newLightColor;
		setModel("Content/Meshes/Sphere.obj");
	}

	void PS_Light::setLightColor(glm::vec3 newColor) {
		lightColor = newColor;
	}
	glm::vec3 PS_Light::getLightColor() {
		return lightColor;
	}
	void PS_Light::makeDirectionalLight() {

	}
	void PS_Light::makePointLight() {

	}
}