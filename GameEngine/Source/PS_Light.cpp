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
	void PS_Light::setDirectional(bool isDirectional) {
		if (isDirectional) {
			setModel("Content/Meshes/Arrow.obj");
			//PS_GameObject::setMeshRotation({ 90, -90, -90 });
			PS_GameObject::setMeshRotation({ 0, 0, 0 });
		}
		else {
			setModel("Content/Meshes/Sphere.obj");
			PS_GameObject::setMeshRotation({ 0, 0, 0 });
		}
		this->isDirectional = isDirectional;
	}

	void PS_Light::setLightColor(glm::vec3 newColor) {
		lightColor = newColor;
	}
	void PS_Light::setIntensity(float newIntensity) {
		intensity = newIntensity;
	}
	glm::vec3 PS_Light::getLightColor() {
		return lightColor;
	}
	float PS_Light::getIntensity() {
		return intensity;
	}
}