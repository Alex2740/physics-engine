#include "Vector3.h"
#include "Rigidbody.h"

// Contient toutes les données concernant un contact
class Contact {

	// Contient 1 ou 2 rigifbody
	// Peut être a remplacer par Primitive
	RigidBody* bodies[2];

	Vector3 contactPoint;

	Vector3 contactNormal;

	float penetration;

	float restitution;

	float friction;
};