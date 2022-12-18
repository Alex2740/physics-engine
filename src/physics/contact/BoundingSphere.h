#pragma once

//#include "physics/contact/primitive/Primitive.h"
//#include "physics/contact/primitive/Box.h"
//#include "physics/contact/primitive/Plane.h"
//#include "physics/contact/primitive/Sphere.h"

#include "core/Vector3.h"

#include <algorithm>

class BoundingSphere {

private :

	Vector3 center;
	float radius;

public :
	BoundingSphere();

	BoundingSphere(Vector3 center, float radius);

	//BoundingSphere(Primitive* primitive);

	//BoundingSphere(Box* box);
	//BoundingSphere(Sphere* sphere);
	//BoundingSphere(Plane* plane);

	BoundingSphere(const BoundingSphere& bs1, const BoundingSphere& bs2);

	float getGrowth(const BoundingSphere &newVolume);

	// Détermine si ce volume est en contact avec le volume other
	bool overlaps(const BoundingSphere& other) const;

	float getSize() const;
};