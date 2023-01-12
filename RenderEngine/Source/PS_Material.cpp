#include "PS_Material.hpp"

namespace ps {
	PS_Material::PS_Material(MaterialComponent newBaseColor) {
		baseColor = newBaseColor;
		baseColor.isTexture = false;
		metallic.isTexture = false;
		specular.isTexture = false;
		roughness.isTexture = false;
		emissive.isTexture = false;
		opacity.isTexture = false;
		opacityMask.isTexture = false;
		normal.isTexture = false;
		ambientOcclusion.isTexture = false;

		baseColor.color = {1, 1, 1};
		metallic.color = { 1, 1, 1 };
		specular.color = { 1, 1, 1 };
		roughness.color = { 1, 1, 1 };
		emissive.color = { 1, 1, 1 };
		opacity.color = { 1, 1, 1 };
		opacityMask.color = { 1, 1, 1 };
		normal.color = { 1, 1, 1 };
		ambientOcclusion.color = { 1, 1, 1 };
	}


	void PS_Material::setColor(MaterialComponent newColor) {
		baseColor = newColor;
	}
	void PS_Material::setMetallic(MaterialComponent newColor) {
		metallic = newColor;
	}
	void PS_Material::setSpecular(MaterialComponent newColor) {
		specular = newColor;
	}
	void PS_Material::setRoughness(MaterialComponent newColor) {
		roughness = newColor;
	}
	void PS_Material::setEmissive(MaterialComponent newColor) {
		emissive = newColor;
	}
	void PS_Material::setOpacity(MaterialComponent newColor) {
		opacity = newColor;
	}
	void PS_Material::setOpacityMask(MaterialComponent newColor) {
		opacityMask = newColor;
	}
	void PS_Material::setNormal(MaterialComponent newColor) {
		normal = newColor;
	}
	void PS_Material::setAmbientOcclusion(MaterialComponent newColor) {
		ambientOcclusion = newColor;
	}

	MaterialComponent PS_Material::getColor() {
		return baseColor;
	}
	MaterialComponent PS_Material::getMetallic() {
		return metallic;
	}
	MaterialComponent PS_Material::getSpecular() {
		return specular;
	}
	MaterialComponent PS_Material::getRoughness() {
		return roughness;
	}
	MaterialComponent PS_Material::getEmissive() {
		return emissive;
	}
	MaterialComponent PS_Material::getOpacity() {
		return opacity;
	}
	MaterialComponent PS_Material::getOpacityMask() {
		return opacityMask;
	}
	MaterialComponent PS_Material::getNormal() {
		return normal;
	}
	MaterialComponent PS_Material::getAmbientOcclusion() {
		return ambientOcclusion;
	}
}