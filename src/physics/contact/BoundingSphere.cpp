#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(Vector3 center, float radius)
{
	this->center = center;
	this->radius = radius;
}

BoundingSphere::BoundingSphere(const BoundingSphere& bs1, const BoundingSphere& bs2)
{

	Vector3 centerOffset = bs2.center - bs1.center;

	float dist = centerOffset.getMagnitude() * centerOffset.getMagnitude();
	float radiusDiff = bs1.radius - bs2.radius;

	// On regarde si la plus grande sphère contient la plus petite
	if (radiusDiff * radiusDiff >= dist) {
		if (bs1.radius > bs2.radius) {
			center = bs1.center;
			radius = bs1.radius;
		}
		else {
			center = bs2.center;
			radius = bs2.radius;
		}

	}
	else {

		dist = centerOffset.getMagnitude();
		radius = (dist + bs1.radius + bs2.radius) * 0.5f;

		// Le nouveau centre est le centre de bs1 décalé vers le centre de bs2
		// par une quantité proportionnel aux rayon des 2 sphères

		center = bs1.center;
		if (dist > 0) {
			center += centerOffset * ((radius - bs1.radius) / dist);
		}
	}
}

bool BoundingSphere::overlaps(const BoundingSphere* other) const
{
	float distanceSquared = (center - other->center).getMagnitude();
	return distanceSquared < (radius + other->radius)* (radius + other->radius);

}
