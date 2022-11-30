#pragma once
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
#include "PS_Mesh.hpp"

namespace ps {
	void PS_Mesh::loadObjects() {
		fs::path curDir = fs::current_path();
		std::string meshDir = curDir.string() + "/Meshes";
		for (const auto& entry : fs::directory_iterator(meshDir)) {
			meshPaths.push_back(entry.path().string());
		}
		std::cout << meshPaths.size() << " .obj files loaded...\n";
	}
}