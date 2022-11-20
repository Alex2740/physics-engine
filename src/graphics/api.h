#pragma once

#include <glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <core/Vector3.h>
#include <core/Matrix4.h>

namespace Graphics
{
	class Api {
	public:
		static glm::vec3 Vector3ToOpenGL(Vector3 vector);
		static glm::mat4 Matrix4ToOpenGL(Matrix4 matrix);
	};
}