#define GLFW_INCLUDE_VULKAN
#include "PS_Test.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    ps::PS_Test app{};
    try {
        app.run();
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}