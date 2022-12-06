#include "core/Vector3.h"
#include "physics/RigidBody.h"

// Contient toutes les donn�es concernant un contact
class Contact {
public:
	RigidBody* body[2];

	Vector3 contactPoint;

	Vector3 contactNormal;

	float penetration;

	float restitution;

	float friction;
};