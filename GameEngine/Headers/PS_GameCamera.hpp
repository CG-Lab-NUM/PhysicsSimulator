#include "PS_GameObject.hpp"

namespace ps {
	class PS_GameCamera : public PS_GameObject {
	public:
		PS_GameCamera();
		glm::vec3 getEye();
		glm::vec3 getCenter();
		glm::vec3 getUp();

	private:
		bool printed = false;
	};
}