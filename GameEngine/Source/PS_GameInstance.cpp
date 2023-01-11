#include "PS_GameInstance.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace ps {
	int PS_GameInstance::startInstance() {
		ps::PS_Renderer app{ &gameLevel };
		try {
			app.run();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
}