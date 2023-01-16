#include "PS_GameMesh.hpp"

namespace ps {
	PS_GameMesh::PS_GameMesh() {
		Vertex vertex;
		vertex.color = { 1, 1, 1, 1 };
		vertex.texCoord = { 0, 0 };
		vertex.pos = { 0, 0, 0 };
		geometryObject.vertices.push_back(vertex);
	}

	PS_GameMesh::PS_GameMesh(GeometryObject3D shape) {
		geometryObject = shape;
	}

	void PS_GameMesh::setMeshGeometryObject(GeometryObject3D shape) {
		geometryObject = shape;
	}

	GeometryObject3D PS_GameMesh::getMeshGeometryObject() {
		return geometryObject;
	}
}