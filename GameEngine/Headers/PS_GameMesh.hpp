#pragma once
#include "PS_RenderGeneric.hpp"

namespace ps {
	class PS_GameMesh {
	public:
		PS_GameMesh();
		PS_GameMesh(GeometryObject3D shape);
		void setMeshGeometryObject(GeometryObject3D shape);
		GeometryObject3D getMeshGeometryObject();
	private:
		GeometryObject3D geometryObject;
	};
}