#include "PS_RenderGeneric.hpp"

namespace ps {
	class PS_KeyboardHandler {
	public:
		static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static bool isPressed(char ch);

		static void setLetterEnabled(bool enabled);
		static void setNumberEnabled(bool enabled);

	private:
		static bool lettersEnabled;
		static bool numbersEnabled;

		static void letterCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static void numberCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

		static std::map<int, bool> currentKeyboard;
	};
}