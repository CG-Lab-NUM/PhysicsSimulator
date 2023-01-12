#pragma once
#include "PS_TextureHandler.hpp"

namespace ps {
	struct MaterialComponent {
		glm::vec3 color;
		PS_TextureHandler *texture;
		bool isTexture;
	};

	class PS_Material {
	public:
		PS_Material();
		void setColor(MaterialComponent newColor);
		void setMetallic(MaterialComponent newColor);
		void setSpecular(MaterialComponent newColor);
		void setRoughness(MaterialComponent newColor);
		void setEmissive(MaterialComponent newColor);
		void setOpacity(MaterialComponent newColor);
		void setOpacityMask(MaterialComponent newColor);
		void setNormal(MaterialComponent newColor);
		void setAmbientOcclusion(MaterialComponent newColor);

		MaterialComponent getColor();
		MaterialComponent getMetallic();
		MaterialComponent getSpecular();
		MaterialComponent getRoughness();
		MaterialComponent getEmissive();
		MaterialComponent getOpacity();
		MaterialComponent getOpacityMask();
		MaterialComponent getNormal();
		MaterialComponent getAmbientOcclusion();

	private:
		MaterialComponent baseColor;
		MaterialComponent metallic;
		MaterialComponent specular;
		MaterialComponent roughness;
		MaterialComponent emissive;
		MaterialComponent opacity;
		MaterialComponent opacityMask;
		MaterialComponent normal;
		MaterialComponent ambientOcclusion;
	};
}