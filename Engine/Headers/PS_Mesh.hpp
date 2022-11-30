#pragma once
#include "PS_Generic.hpp"

namespace ps {
	class PS_Mesh {
	public:
		PS_Mesh() {
			loadObjects();
			loadMaterials();		
		}

		~PS_Mesh() {

		}
		PS_Mesh(const PS_Mesh&) = delete;
		PS_Mesh& operator = (const PS_Mesh&) = delete;

		std::vector<std::string> meshPaths;
		std::vector<std::string> materialPaths;

	private:
		void loadObjects();
		void loadMaterials();
	};
}