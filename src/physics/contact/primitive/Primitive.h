#pragma once

#include "physics/Rigidbody.h"

enum PrimitiveType {
	PrimitiveBox,
	PrimitiveSphere,
	PrimitivePlane
};

class Primitive
{
public:
	// RigidBody attache a la primitive
	RigidBody* body;

	// Offset entre la position du body et le centre de la primitive
	Matrix4 offset;

	virtual PrimitiveType getType() = 0;
};