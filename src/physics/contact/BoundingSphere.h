#include "Vector3.h"

class BoundingSphere {

private :

	Vector3 center;
	float radius;

public :

	BoundingSphere(Vector3 center, float radius);

	BoundingSphere(const BoundingSphere& bs1, const BoundingSphere& bs2);

	// D�termine si ce volume est en contact avec le volume other
	bool overlaps(const BoundingSphere* other) const;
};