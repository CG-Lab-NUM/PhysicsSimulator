#define GLFW_INCLUDE_VULKAN
#include "PS_App.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    ps::PS_App app{};
    try {
        app.run();
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}