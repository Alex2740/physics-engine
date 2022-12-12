#pragma once
#include "core/Vector3.h"
#include "physics/RigidBody.h"

// Contient toutes les données concernant un contact
class Contact {
public:
	int type; // type de contact:
			  // 0: sphere & sphere
			  // 1: sphere and halfspace
			  // 2: sphere and plane
			  // 3: sphere and point
			  // 4: box and half space
			  // 5: box and sphere
			  // 6: box and box
			  // 7: box and point
			  // 8: box and plane

	RigidBody* body[2];

	Vector3 contactPoint;

	Vector3 contactNormal;

	float penetration;

	float restitution;

	float friction;
};