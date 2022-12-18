#pragma once

#include "Primitive.h"

class Sphere : public Primitive
{
public:
	// Radius de la sphere
	float radius;

	int getType() override;
};