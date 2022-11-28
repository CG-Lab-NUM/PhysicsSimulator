#pragma once
#include "PS_Window.hpp"
#include <vector>
#include <optional>
#include <set>
#include <limits>
#include <algorithm>

namespace ps {
	class PS_Device {
	public:
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		std::vector<VkImageView> swapChainImageViews;

		struct QueueFamilyIndices {
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;

			bool isComplete() {
				return graphicsFamily.has_value() && presentFamily.has_value();
			}
		};

		void createInstance();
		void pickPhysicalDevice(VkSurfaceKHR surface);
		void createLogicalDevice();

		bool checkValidationLayerSupport();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		std::vector<const char*> getRequiredExtensions();
		void setupDebugMessenger();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		
		//
		// Swap Chain
		//
		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};
		void createSwapChain(VkSurfaceKHR surface, GLFWwindow* window);
		void createImageViews();

		//
		// Getters
		//
		VkInstance getInstance() {
			return instance;
		}
		VkDevice getDevice() {
			return device;
		}
		VkPhysicalDevice getPhysicalDevice() {
			return physicalDevice;
		}
		VkFormat getSwapChainImageFormat() {
			return swapChainImageFormat;
		}

		// 
		// Setters
		//
		void setSurface(VkSurfaceKHR surface) {
			this->surface = surface;
		}

	private:
		PS_Logger psLogger;

		VkQueue graphicsQueue;
		VkDevice device;
		VkQueue presentQueue;
		VkSurfaceKHR surface;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;

		//
		// Swap Chain
		//
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
	};
}