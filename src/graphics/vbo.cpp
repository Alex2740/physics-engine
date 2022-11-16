#include "vbo.h"

Graphics::VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void Graphics::VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void Graphics::VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Graphics::VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
