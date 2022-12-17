#pragma once

#include <physics/Rigidbody.h>

class Primitive
{
public:
	// RigidBody attache a la primitive
	RigidBody* body;

	// Offset entre la position du body et le centre de la primitive
	Matrix4 offset;

	virtual int getType() = 0;
	// box = 0
	// sphere = 1
	// plane = 2
};