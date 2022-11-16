#include "Rigidbody.h"

Vector3 RigidBody::getPointInWorldSpace(Vector3 point)
{
	return Matrix4::localToWorld(point, transformMatrix);
}

RigidBody::RigidBody(Vector3 position,float a, float b, float c ,float masse, float linearDamping, float angularDamping)
{
	// Rigidbody : parallélépipède rectangle 
	// a : longueur
	// b : largeur
	// c : hauteur

	Matrix3 inertie;
	inertie.data[0] = (masse / 12)  * (powf(c, 2) + powf(b, 2));
	inertie.data[4] = (masse / 12)  * (powf(a, 2) + powf(c,2));
	inertie.data[8] = (masse / 12) * (powf(a, 2) + powf(b, 2));
	

	// Calcul du tenseur d'inertie inverse
	inverseInertiaTensorLocal = inertie.inverse();
	

	this->position = position;
	this->inverseMasse = 1 / masse;
	this->damping = linearDamping;
	this->angularDamping = angularDamping;
}

void RigidBody::integrate(float dt)
{
	// MaJ de la position
	position += velocity * dt;

	// MaJ de l'orientation

	orientation += Quaternion(0, rotation) * orientation * dt/2;

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
	transformMatrix.data[1] = 2 * (orientation.x * orientation.y + orientation.z * orientation.w);
	transformMatrix.data[2] = 2 * (orientation.x * orientation.z - orientation.y * orientation.w);
	transformMatrix.data[3] = position.x;

	transformMatrix.data[4] = 2 * (orientation.x * orientation.y - orientation.z * orientation.w);
	transformMatrix.data[5] = 1 - 2 * (orientation.x * orientation.x + orientation.z * orientation.z);
	transformMatrix.data[6] = 2 * (orientation.y * orientation.z + orientation.x * orientation.w);
	transformMatrix.data[7] = position.y;

	transformMatrix.data[8] = 2 * (orientation.x * orientation.y + orientation.y * orientation.w);
	transformMatrix.data[9] = 2 * (orientation.y * orientation.z - orientation.x * orientation.w);
	transformMatrix.data[10] = 1 - 2 * (orientation.x * orientation.x + orientation.y * orientation.y);
	transformMatrix.data[11] = position.z;
	


	// Calcul de l'inverse de la matrice du tenseur d'inertie dans les coordonnées globale
	// I(-1)' = MbI(-1)Mb(-1)
	// Mb matrice 3x3 (rotation, on ne s'intéresse pas à la translation)

	// Calcul MbI(-1)
	{
	// old version
	// float i0 = transformMatrix.data[0] * inverseInertiaTensorLocal.data[0]
	// 	+ transformMatrix.data[1] * inverseInertiaTensorLocal.data[3]
	// 	+ transformMatrix.data[2] * inverseInertiaTensorLocal.data[6];

	// float i1= transformMatrix.data[0] * inverseInertiaTensorLocal.data[1]
	// 	+ transformMatrix.data[1] * inverseInertiaTensorLocal.data[4]
	// 	+ transformMatrix.data[2] * inverseInertiaTensorLocal.data[7];

	// float i2= transformMatrix.data[0] * inverseInertiaTensorLocal.data[2]
	// 	+ transformMatrix.data[1] * inverseInertiaTensorLocal.data[5]
	// 	+ transformMatrix.data[2] * inverseInertiaTensorLocal.data[8];

	// float i3 = transformMatrix.data[3] * inverseInertiaTensorLocal.data[0]
	// 	+ transformMatrix.data[4] * inverseInertiaTensorLocal.data[3]
	// 	+ transformMatrix.data[5] * inverseInertiaTensorLocal.data[6];

	// float i4 = transformMatrix.data[3] * inverseInertiaTensorLocal.data[1]
	// 	+ transformMatrix.data[4] * inverseInertiaTensorLocal.data[4]
	// 	+ transformMatrix.data[5] * inverseInertiaTensorLocal.data[7];

	// float i5 = transformMatrix.data[3] * inverseInertiaTensorLocal.data[2]
	// 	+ transformMatrix.data[4] * inverseInertiaTensorLocal.data[5]
	// 	+ transformMatrix.data[5] * inverseInertiaTensorLocal.data[8];

	// float i6 = transformMatrix.data[6] * inverseInertiaTensorLocal.data[0]
	// 	+ transformMatrix.data[7] * inverseInertiaTensorLocal.data[3]
	// 	+ transformMatrix.data[8] * inverseInertiaTensorLocal.data[6];

	// float i7 = transformMatrix.data[6] * inverseInertiaTensorLocal.data[1]
	// 	+ transformMatrix.data[7] * inverseInertiaTensorLocal.data[4]
	// 	+ transformMatrix.data[8] * inverseInertiaTensorLocal.data[7];

	// float i8 = transformMatrix.data[6] * inverseInertiaTensorLocal.data[2]
	// 	+ transformMatrix.data[7] * inverseInertiaTensorLocal.data[5]
	// 	+ transformMatrix.data[8] * inverseInertiaTensorLocal.data[8];
	}
	Matrix3 transformeMatrix3, tmp;
	transformeMatrix3 = transformMatrix.getMatrix3();
	tmp = transformeMatrix3 * inverseInertiaTensorLocal;

	//Calcul MbI(-1)Mb(-1) = I(-1)'
	// Les deux bases sont orthonormées, donc la matrice Mb est orthogonale
	// On a alors Mb(-1) = (t)Mb, ce qui simplifie le calcul

	{
	// old version	
	// inverseInertiaTensorWorld.data[0] = i0 * transformMatrix.data[0]
	// 	+ i1 * transformMatrix.data[1] + i2 * transformMatrix.data[2];
	
	// inverseInertiaTensorWorld.data[1] = i0 * transformMatrix.data[4]
	// 	+ i1 * transformMatrix.data[5] + i2 * transformMatrix.data[6];

	// inverseInertiaTensorWorld.data[2] = i0 * transformMatrix.data[8]
	// 	+ i1 * transformMatrix.data[9] + i2 * transformMatrix.data[10];

	// inverseInertiaTensorWorld.data[3] = i3 * transformMatrix.data[0]
	// 	+ i4 * transformMatrix.data[1] + i5 * transformMatrix.data[2];

	// inverseInertiaTensorWorld.data[4] = i3 * transformMatrix.data[4]
	// 	+ i4 * transformMatrix.data[5] + i5 * transformMatrix.data[6];

	// inverseInertiaTensorWorld.data[5] = i3 * transformMatrix.data[8]
	// 	+ i4 * transformMatrix.data[9] + i5 * transformMatrix.data[10];

	// inverseInertiaTensorWorld.data[6] = i6 * transformMatrix.data[0]
	// 	+ i7 * transformMatrix.data[1] + i8 * transformMatrix.data[2];

	// inverseInertiaTensorWorld.data[7] = i6 * transformMatrix.data[4]
	// 	+ i7 * transformMatrix.data[5] + i8 * transformMatrix.data[6];

	// inverseInertiaTensorWorld.data[8] = i6 * transformMatrix.data[8]
	// 	+ i7 * transformMatrix.data[9] + i8 * transformMatrix.data[10];
	}

	inverseInertiaTensorWorld = tmp * transformeMatrix3.inverse();

}
