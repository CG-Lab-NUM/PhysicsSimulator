#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "PS_Window.hpp"

namespace ps {
	class PS_ColorHandler {
	public:
		static glm::vec3 makeColor(std::string hex) {
			std::string temp = "";
			for (int i = 0; i < 2; i++) {
				temp += hex[i];
			}
			int r = std::stoi(temp, NULL, 16);
			float r_f = (float)r / 255;
			temp = "";
			for (int i = 2; i < 4; i++) {
				temp += hex[i];
			}
			int g = std::stoi(temp, NULL, 16);
			float g_f = (float)g / 255;
			temp = "";
			for (int i = 4; i < 6; i++) {
				temp += hex[i];
			}
			int b = std::stoi(temp, NULL, 16);
			float b_f = (float)b / 255;
			return { r_f, g_f, b_f };
		}
	};
}