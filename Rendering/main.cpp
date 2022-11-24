#define GLFW_INCLUDE_VULKAN
#include "TestApp.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    ps_window::TestApp app{};
    try {
        app.run();
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}