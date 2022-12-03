#pragma once

#include "core/Vector3.h"

class Plane
{
public:
	// Normal du plan
	Vector3 normal;

	// Offset du plan par rapport a l'origine
	float offset;
};