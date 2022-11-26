#include "PS_Logger.hpp"

#include <string>
#include <fstream>
#include <vulkan/vk_enum_string_helper.h>

namespace ps {
    void PS_Logger::LogResult(const VkResult result) {
        std::ofstream log("Logs/result_log.txt");
        if (log.is_open()) {
            log << string_VkResult(result);
            log.close();
        }
    }
}