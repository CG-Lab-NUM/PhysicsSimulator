#pragma once
#include "PS_Window.hpp"
#include <vector>
#include <optional>
#include <set>
#include <limits>
#include <algorithm>

namespace ps {

	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif

		class PS_Device {
		public:
		PS_Device() {

		}
		~PS_Device();
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
		void cleanDevice();

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
		VkImageView createImageView(VkImage image, VkFormat format);
		
		//
		// Swap Chain
		//
		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};
		void createSwapChain(PS_Window *psWindow);
		void createImageViews();
		void createFramebuffers(VkRenderPass renderPass);
		void createCommandPool();
		void createSyncObjects();
		void recreateSwapChain(PS_Window* psWindow, VkRenderPass renderPass);

		std::vector<VkImage> swapChainImages;
		std::vector<VkFramebuffer> swapChainFramebuffers;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		//
		// Graphics
		//

		VkQueue graphicsQueue;
		VkQueue presentQueue;
		//
		// Semaphores
		//
		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		uint32_t currentFrame = 0;
		const int MAX_FRAMES_IN_FLIGHT = 2;

		//
		// Getters & Setters
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
		VkQueue getGraphicsQueue() {
			return graphicsQueue;
		}
		VkQueue getPresentQueue() {
			return presentQueue;
		}
		VkCommandPool getCommandPool() {
			return commandPool;
		}
		VkSwapchainKHR getSwapChain() {
			return swapChain;
		}
		void setSurface(VkSurfaceKHR surface) {
			this->surface = surface;
		}

	private:
		PS_Logger psLogger{};

		VkDevice device;
		VkSurfaceKHR surface;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

		VkSwapchainKHR swapChain;
		VkCommandPool commandPool;

		//
		// Swap Chain
		//
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
	};
}