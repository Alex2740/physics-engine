#pragma once

#include "IForceAppliable.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "Matrix3.h"

class RigidBody: IForceAppliable {

private : 
	float inverseMasse;
	float linearDamping;

	Quaternion orientation;
	Vector3 rotation;
	Matrix4 transformMatrix;

	float angularDamping;
	// Vector3 acceleration;
	Vector3 torqueAccum;

	Matrix3 inverseInertiaTensorLocal;
	Matrix3 inverseInertiaTensorWorld;

	Vector3 getPointInWorldSpace(Vector3 point);

public : 
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	
	void integrate(float dt);

	void addForce(const Vector3& force);

	void AddForceAtPoint(const Vector3& force, const Vector3& worldPoint);

	void AddForceAtBodyPoint(const Vector3& force, const Vector3& localPoint);

	void ClearAccumulator();

private :

	void CalculateDerivedData();

};