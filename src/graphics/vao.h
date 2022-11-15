#pragma once

#include<glad/glad.h>
#include"vbo.h"

namespace Graphics {
	class VAO
	{
	public:
		GLuint ID;

		VAO();

		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
	};
}