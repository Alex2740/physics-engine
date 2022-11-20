#include "api.h"

glm::vec3 Graphics::Api::Vector3ToOpenGL(Vector3 vector)
{
	return glm::vec3(vector.x, vector.y, vector.z);
}

glm::mat4 Graphics::Api::Matrix4ToOpenGL(Matrix4 matrix)
{
	float data[16];
	for (int i = 0; i < 12; i++) data[i] = matrix.data[i];

	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;

	return glm::make_mat4(data);
}
