#pragma once

#include "Primitive.h"
#include "core/Vector3.h"
#include <stdexcept>

class Plane : public Primitive
{
public:
	// Normal du plan
	Vector3 normal;

	// Offset du plan par rapport a l'origine
	float offset;

	bool isIncludePoint(Vector3 point);

	// get distance (with negative as the other side of normal) to a certain point in space
	float getDistanceToPoint(Vector3 point);

	int getType() override;
};