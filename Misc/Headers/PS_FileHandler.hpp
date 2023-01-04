#pragma once
#include "PS_RenderGeneric.hpp"

namespace ps {
	class PS_FileHandler {
	public:
		std::string makeAbsolute(std::string path);
	private:
		std::string getWorkingDirectory();
	};
}