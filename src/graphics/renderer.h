#pragma once
#include "physics/Rigidbody.h"
#include "graphics/texture.h"
#include "graphics/vao.h"
#include "graphics/vbo.h"
#include "graphics/ebo.h"

class Renderer
{
public:
	static VAO vertexArrayObject;
	static void Init();
	static void Delete();
	static void RenderCube(RigidBody cube, Shader shaderProgram, Texture texture);
};
