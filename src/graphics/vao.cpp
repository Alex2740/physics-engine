#include "vao.h"

Graphics::VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void Graphics::VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void Graphics::VAO::Bind()
{
	glBindVertexArray(ID);
}

void Graphics::VAO::Unbind()
{
	glBindVertexArray(0);
}

void Graphics::VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
