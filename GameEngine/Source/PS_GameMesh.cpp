#include "PS_GameMesh.hpp"

namespace ps {
	void PS_GameMesh::makeCube(glm::vec3 center, float edgeLength) {
        int h = edgeLength / 2;
        std::vector<glm::vec3> vertexLocations;
        for (int i = 0; i < 8; i++) {
            glm::vec3 temp = {
                (i & 4) != 0 ? h : -h,
                (i & 2) != 0 ? h : -h,
                (i & 1) != 0 ? h : -h
            };
            temp = temp + center;
            Vertex vertex;
            vertex.pos = temp;
            //vertex.color = { 1.0f, 1.0f, 1.0f };
            vertex.texCoord = { 0.0f, 0.0f };
            vertices.push_back(vertex);
        }
	}
}