#pragma once
#include "PS_Generic.hpp"

namespace ps {
	class PS_Mesh {
	public:
		PS_Mesh() {
			loadObjects();
		}

		~PS_Mesh() {

		}
		PS_Mesh(const PS_Mesh&) = delete;
		PS_Mesh& operator = (const PS_Mesh&) = delete;

		const std::string TEXTURE_PATH;
		std::vector<std::string> meshPaths;
		int meshCount = 0;

	private:
		void loadObjects();
	};
}