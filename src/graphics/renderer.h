#pragma once
#include "physics/Rigidbody.h"
#include "graphics/texture.h"
#include "graphics/vao.h"
#include "graphics/vbo.h"
#include "graphics/ebo.h"

#include <map>

class Renderer
{
private:
	VAO vertexArrayObject;
	std::map<RigidBody*, Texture*> textureMap;
public:
	Renderer();

	void Delete();
	void RenderCube(RigidBody* cube, Shader shaderProgram);
	void BindTexture(RigidBody* rigidbody, Texture* texture);
};
