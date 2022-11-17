#pragma once

#include "IForceAppliable.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "Matrix3.h"

class RigidBody: public IForceAppliable {

private:
	Quaternion orientation;
	Vector3 rotation; // vitesse angulaire
	Matrix4 transformMatrix;

	float angularDamping;
	// Vector3 acceleration;
	Vector3 torqueAccum;

	Matrix3 inverseInertiaTensorLocal;
	Matrix3 inverseInertiaTensorWorld;

	void CalculateDerivedData();

public:
	// Vector3 position;
	// Vector3 velocity;
	// Vector3 acceleration;


	RigidBody(Vector3 position , float a, float b, float c ,float masse, float linearDamping, float angularDamping);

	void integrate(float dt) override;

	void addForce(const Vector3& force);

	void AddForceAtPoint(const Vector3& force, const Vector3& worldPoint);

	void AddForceAtBodyPoint(const Vector3& force, const Vector3& localPoint);

	void ClearAccumulator();
	Vector3 getPointInWorldSpace(Vector3 point);


};