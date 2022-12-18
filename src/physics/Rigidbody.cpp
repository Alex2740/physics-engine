#include "Rigidbody.h"
#include <iostream>
#include <fstream>

Vector3 RigidBody::getPointInWorldSpace(Vector3 point)
{
	return Matrix4::localToWorld(point, transformMatrix);
}

RigidBody::RigidBody(Vector3 position, Vector3 size, float masse, float linearDamping, float angularDamping)
{
	// Rigidbody : parallélépipède rectangle 
	// a : longueur x
	// b : largeur z
	// c : hauteur y
	id = comptId;
	comptId++;

	Matrix3 inertie = Matrix3();
	inertie.data[0] = (masse / 12)  * (powf(size.z, 2) + powf(size.y, 2));
	inertie.data[4] = (masse / 12)  * (powf(size.x, 2) + powf(size.y, 2));
	inertie.data[8] = (masse / 12) * (powf(size.x, 2) + powf(size.z, 2));
	
	// Calcul du tenseur d'inertie inverse
	inverseInertiaTensorLocal = inertie.inverse();
	

	this->position = position;
	this->orientation = Quaternion::Identity();
	this->rotation = Vector3::Zero();
	this->inverseMasse = 1 / masse;
	this->damping = linearDamping;
	this->angularDamping = angularDamping;
	this->size = size;

	dirtyRadiusBS = true;
	radiusBS = -1;

	CalculateDerivedData();
}

void RigidBody::integrate(float dt)
{
	// MaJ de la position
	position += velocity * dt;

	// MaJ de l'orientation
	// Quaternion tmp = (Quaternion(0, rotation) * orientation);
	orientation += Quaternion(0, rotation) * orientation * dt/2;
	// Quaternion tmp2 = orientation;
	orientation = Quaternion::normalize(orientation);

	CalculateDerivedData();

	// Calcul accélération linéaire
	Vector3 linearAcceleration = acceleration * inverseMasse;

	// Calcul accélération angulaire
	Vector3 angularAcceleration = inverseInertiaTensorWorld.transform(torqueAccum);

	// Calcul vélocité linéaire
	velocity = velocity * powf(damping, dt) + linearAcceleration * dt;

	// Calcul vélocité angulaire
	rotation = rotation * powf(angularDamping, dt) + angularAcceleration * dt;



	ClearAccumulator();

}

void RigidBody::addForce(const Vector3& force)
{
	// Utile pour des force comme la gravité qui s'applique au centre de masse et n'influence pas la rotation
	acceleration += force;
}

void RigidBody::AddForceAtPoint(const Vector3& force, const Vector3& worldPoint)
{
	Vector3 point = worldPoint;

	point -= position;

	acceleration += force;
	torqueAccum += Vector3::Cross(point, force);
}

void RigidBody::AddForceAtBodyPoint(const Vector3& force, const Vector3& localPoint)
{
	Vector3 worldPoint = getPointInWorldSpace(localPoint);

	AddForceAtPoint(force, worldPoint);
}

void RigidBody::ClearAccumulator()
{
	acceleration = Vector3::Zero();
	torqueAccum = Vector3::Zero();
}

void RigidBody::CalculateDerivedData()
{
	// normaliser orietnation à cause des imprécisions numériques ?

	// Calcul matrice de transformation

	transformMatrix.data[0] = 1 - 2 * (orientation.y * orientation.y + orientation.z * orientation.z);
	transformMatrix.data[1] = 2 * (orientation.x * orientation.y - orientation.z * orientation.w);
	transformMatrix.data[2] = 2 * (orientation.x * orientation.z + orientation.y * orientation.w);
	transformMatrix.data[3] = position.x;

	transformMatrix.data[4] = 2 * (orientation.x * orientation.y + orientation.z * orientation.w);
	transformMatrix.data[5] = 1 - 2 * (orientation.x * orientation.x + orientation.z * orientation.z);
	transformMatrix.data[6] = 2 * (orientation.y * orientation.z - orientation.x * orientation.w);
	transformMatrix.data[7] = position.y;

	transformMatrix.data[8] = 2 * (orientation.x * orientation.y - orientation.y * orientation.w);
	transformMatrix.data[9] = 2 * (orientation.y * orientation.z + orientation.x * orientation.w);
	transformMatrix.data[10] = 1 - 2 * (orientation.x * orientation.x + orientation.y * orientation.y);
	transformMatrix.data[11] = position.z;
	// I(-1)' = Mb * I(-1) * Mb(-1)

	Matrix3 mb = transformMatrix.getMatrix3();
	inverseInertiaTensorWorld = mb * inverseInertiaTensorLocal * mb.inverse();
}

Quaternion RigidBody::getOrientation() {
	return this->orientation;
}

int RigidBody::getId() { return id; }

float RigidBody::getRadiusBoundingSphere()
{
	if (dirtyRadiusBS) {
		Vector3 halfSize = size / 2;
		radiusBS = halfSize.getMagnitude();

		dirtyRadiusBS = false;
	}

	return radiusBS;
}

BoundingSphere RigidBody::createBoundingSphere()
{
	return BoundingSphere(position, getRadiusBoundingSphere());
}

int RigidBody::comptId = 0;