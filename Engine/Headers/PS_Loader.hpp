#pragma once
#include "PS_Generic.hpp"
#include <filesystem>

namespace ps {
	class PS_Loader {
	public:
		PS_Loader() {
			loadObjects();
			loadMaterials();		
		}

		~PS_Loader() {

		}
		PS_Loader(const PS_Loader&) = delete;
		PS_Loader& operator = (const PS_Loader&) = delete;

		std::vector<std::string> meshPaths;
		std::vector<std::string> materialPaths;

	private:
		void loadObjects();
		void loadMaterials();
		void addFilesRecursive(const std::string path);
	};
}