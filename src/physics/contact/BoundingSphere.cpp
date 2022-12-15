#include "BoundingSphere.h"

BoundingSphere::BoundingSphere()
{
	center = Vector3::Zero();
	radius = 0.0f;
}

BoundingSphere::BoundingSphere(Vector3 center, float radius)
{
	this->center = center;
	this->radius = radius;
}

BoundingSphere::BoundingSphere(const BoundingSphere& bs1, const BoundingSphere& bs2)
{

	//Vector3 centerOffset = bs2.center - bs1.center;
	//float dist = centerOffset.getMagnitude() * centerOffset.getMagnitude();

	float SquareDist = Vector3::Distance(bs2.center, bs1.center) * Vector3::Distance(bs2.center, bs1.center);

	float radiusDiff = bs1.radius - bs2.radius;

	// On regarde si la plus grande sphère contient la plus petite
	if (radiusDiff * radiusDiff >= SquareDist) {
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

		float dist = Vector3::Distance(bs2.center, bs1.center);
		radius = (dist + bs1.radius + bs2.radius) * 0.5f;

		// Le nouveau centre est le centre de bs1 décalé vers le centre de bs2
		// par une quantité proportionnel aux rayon des 2 sphères

		center = bs1.center;
		if (dist > 0) {
			center += (bs2.center - bs1.center) * ((radius - bs1.radius) / dist);
		}
	}
}

float BoundingSphere::getGrowth(const BoundingSphere& newVolume)
{
	// Calcul du rayon de la sphère englobant la sphère actuelle et la sphère newVolume

	// On calcule d'abord la distance entre les deux centres
	float dist = Vector3::Distance(center, newVolume.center);

	// On ajoute à cette distance les 2 rayons pour obtenir le diamètre de la nouvelle sphère englobante
	dist += radius + newVolume.radius;

	// On retourne le rayon de la nouvelle sphère
	return dist / 2;
}

bool BoundingSphere::overlaps(const BoundingSphere& other) const
{
	float distanceSquared = Vector3::Distance(center, other.center) * Vector3::Distance(center, other.center);
	return distanceSquared < (radius + other.radius)* (radius + other.radius);

}

float BoundingSphere::getSize() const
{
	return radius;
}
