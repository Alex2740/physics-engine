#include "Vector3.h"
#include "RigidBody.h"

// Contient toutes les données concernant un contact
class Contact {
public:
	RigidBody* body[2];

	Vector3 contactPoint;

	Vector3 contactNormal;

	float penetration;

	float restitution;

	float friction;
};