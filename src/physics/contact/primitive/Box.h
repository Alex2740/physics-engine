#pragma once

#include "Primitive.h"

#include <array>

class Box : public Primitive
{
public:
	// Demi taille de la boite
	Vector3 halfSize;

	std::array<Vector3, 8> getLocalCoordVertices();

	Vector3 getAxis(int i);
	float projectOnAxis(Vector3 axis);

	PrimitiveType getType() override;
};