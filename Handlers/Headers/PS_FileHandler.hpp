#pragma once
#include "PS_RenderGeneric.hpp"

namespace ps {
	class PS_FileHandler {
	public:
		static std::string makeAbsolute(std::string path);
		static std::vector<char> readFile(const std::string& fileName);
	private:
		static std::string getWorkingDirectory();
	};
}