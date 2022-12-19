#pragma once
#include "core/Vector3.h"
#include "physics/RigidBody.h"

enum ContactType {
	SphereSphere,
	SphereHalfSpace,
	SpherePlane,
	SpherePoint,
	BoxHalfSpace,
	BoxSphere,
	BoxBox,
	BoxPoint,
	BoxPlane,
	ContactNull
};

// Contient toutes les données concernant un contact
class Contact {
public:
	ContactType type;

	RigidBody* body[2];

	Vector3 contactPoint;

	Vector3 contactNormal;

	float penetration;

	float restitution;

	float friction;

	static Contact ContactNull();

	bool operator==(const Contact& other) const;
	bool operator!=(const Contact& other) const;
};