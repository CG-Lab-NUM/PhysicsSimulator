#include "PS_EngineGeneric.hpp"

namespace ps {
	class PS_GameMesh {
	public:
		void makeCube(glm::vec3 center, float edgeLength);

		std::vector<Vertex> vertices;
	private:
	};
}