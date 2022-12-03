#pragma once

#include "Primitive.h"

class Box : public Primitive
{
public:
	// Demi taille de la boite
	Vector3 halfSize;
};