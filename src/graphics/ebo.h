#pragma once

#include <glad/glad.h>

namespace Graphics {
	class EBO
	{
	public:
		GLuint ID;

		EBO(GLuint* indices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
	};
}