#pragma once
#include <string>
#include <iostream>
#include "PS_Loader.hpp"

namespace ps {
	void PS_Loader::loadObjects() {
		std::filesystem::path curDir = std::filesystem::current_path();
		std::string meshDir = curDir.string() + "/Meshes";
		for (const auto& entry : std::filesystem::directory_iterator(meshDir)) {
			meshPaths.push_back(entry.path().string());
		}
		std::cout << meshPaths.size() << " .obj files loaded...\n";
	}

	void PS_Loader::loadMaterials() {
		std::filesystem::path curDir = std::filesystem::current_path();
		std::string textureDir = curDir.string() + "/Textures";
		addFilesRecursive(textureDir);
		std::cout << materialPaths.size() << " texture files loaded...\n";
	}

	void PS_Loader::addFilesRecursive(const std::string path) {
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (std::filesystem::is_directory(entry)) {
				std::string new_path = entry.path().string();
				addFilesRecursive(new_path);
;			}
			else {
				materialPaths.push_back(entry.path().string());
			}
		}

	}
}