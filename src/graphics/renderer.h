#pragma once
#include "physics/Rigidbody.h"
#include "graphics/texture.h"
#include "graphics/vao.h"
#include "graphics/vbo.h"
#include "graphics/ebo.h"

class Renderer
{
private:
	VAO vertexArrayObject;
public:
	Renderer();

	void Delete();
	void RenderCube(RigidBody cube, Shader shaderProgram, Texture texture);
};
