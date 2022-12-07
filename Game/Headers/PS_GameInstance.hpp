#include "PS_App.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace ps {
	class PS_GameInstance {
	public:
		int startInstance() {
			ps::PS_App app{};
			try {
				app.run();
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << '\n';
				return EXIT_FAILURE;
			}
		}
	private:
	};
}