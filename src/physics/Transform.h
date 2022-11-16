#pragma once

#include "Vector3.h"
#include "Matrix4.h"

class Transform
{
public:
	static Vector3 LocalToWorld(Vector3& local, Matrix4& transform);
	static Vector3 WorldToLocal(Vector3& world, Matrix4& transform);
};