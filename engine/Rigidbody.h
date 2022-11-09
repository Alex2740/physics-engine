#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "Matrix3.h"

class RigidBody {

private : 
	float inverseMasse;
	float linearDamping;
	Vector3 position;
	Vector3 velocity;

	Quaternion orientation;
	Vector3 rotation;
	Matrix4 transformMatrix;

	float angularDamping;
	Vector3 forceAccum;
	Vector3 torqueAccum;

	Matrix3 inverseInertiaTensorLocal;
	Matrix3 inverseInertiaTensorWorld;

public : 
	
	void Intergrate(float dt);

	void AddForce(const Vector3& force);

	void AddForceAtPoint(const Vector3& force, const Vector3& worldPoint);

	void AddForceAtBodyPoint(const Vector3& force, const Vector3& localPoint);

	void ClearAccumulator();

private :

	void CalculateDerivedData();


};