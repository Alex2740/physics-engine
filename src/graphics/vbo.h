#pragma once

#include <glad/glad.h>

namespace Graphics {
	class VBO
	{
	public:
		GLuint ID;

		VBO(GLfloat* vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
	};
}