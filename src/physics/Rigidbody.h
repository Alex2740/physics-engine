#pragma once

#include "physics/IForceAppliable.h"
#include "core/Vector3.h"
#include "core/Quaternion.h"
#include "core/Matrix4.h"
#include "core/Matrix3.h"
#include "physics/contact/BoundingSphere.h"

class RigidBody: public IForceAppliable {

private:
	static int comptId;

	int id;

	Vector3 rotation; // vitesse angulaire
	Matrix4 transformMatrix;

	float angularDamping = 1;
	// Vector3 acceleration;
	

	Matrix3 inverseInertiaTensorLocal;
	Matrix3 inverseInertiaTensorWorld;

	void CalculateDerivedData();

	bool dirtyRadiusBS;
	float radiusBS;

public:
	// Vector3 position;
	// Vector3 velocity;
	// Vector3 acceleration;
	Quaternion orientation;
	Vector3 size;
	Vector3 torqueAccum = Vector3::Zero();


	RigidBody(Vector3 position, Vector3 size, float masse, float linearDamping, float angularDamping);

	void integrate(float dt) override;

	void addForce(const Vector3& force);

	void AddForceAtPoint(const Vector3& force, const Vector3& worldPoint);

	void AddForceAtBodyPoint(const Vector3& force, const Vector3& localPoint);

	void ClearAccumulator();
	Vector3 getPointInWorldSpace(Vector3 point);

	Quaternion getOrientation();

	int getId();

	float getRadiusBoundingSphere();
	BoundingSphere createBoundingSphere();
};
