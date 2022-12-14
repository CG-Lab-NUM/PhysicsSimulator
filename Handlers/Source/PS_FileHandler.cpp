#include "PS_FileHandler.hpp"
#ifdef _WIN64
#include <direct.h>
#define getCurrentDir _getcwd
#else
#include <unistd.h>
#define getCurrentDir getcwd
#endif


namespace ps {
	std::string PS_FileHandler::makeAbsolute(std::string path) {
		std::string absolutePath = getWorkingDirectory() + "/" + path;
		return absolutePath;
	}

	std::string PS_FileHandler::getWorkingDirectory() {
		char buff[FILENAME_MAX]; //create string buffer to hold path
		getCurrentDir(buff, FILENAME_MAX);
		std::string current_working_dir(buff);
		return current_working_dir.c_str();
	}

	std::vector<char> PS_FileHandler::readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			std::string err = "Failed to open file: " + filename;
			throw std::runtime_error(err);
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}
}