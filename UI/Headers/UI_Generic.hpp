#pragma once

namespace ps {
	struct GeometryObject2D {
		float x;
		float y;
		float width;
		float height;
		glm::vec4 color;
		float xRotation;
		float yRotation;
	};

	struct GeometrySquare {
		float x;
		float y;
		float width;
		float height;
		float xRotation;
		float yRotation;
	};
}