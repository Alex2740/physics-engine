#include "Vector3.h"

class BoudingSphere {

private :

	Vector3 center;
	float radius;

public :

	BoudingSphere(Vector3 center, float radius);

	// D�termine si ce volume est en contact avec le volume other
	bool overlaps(const BoudingSphere* other) const;
};