#pragma once

#include "physics/contact/primitive/Sphere.h"
#include "physics/contact/primitive/Plane.h"
#include "physics/contact/primitive/Box.h"
#include "physics/contact/CollisionData.h"

#include <vector>
#include <algorithm> 
#include <cmath>
#include <limits>

class CollisionDetector
{
private:
	static std::vector<Vector3> generateSATAllAxis(Box& one, Box& two);
	static Contact createContactPointFace(Box& boxOfPoint, Box& boxOfFace, Vector3 axis, float interpenetration);

public:
	static int SphereAndSphere(Sphere& one, Sphere& two, CollisionData* data);
	static int SphereAndHalfSpace(Sphere& one, Plane& two, CollisionData* data);
	static int SphereAndPlane(Sphere& one, Plane& two, CollisionData* data);
	static int SphereAndPoint(Sphere& one, Vector3& two, CollisionData* data);
	static int BoxAndHalfSpace(Box& one, Plane& two, CollisionData* data);
	static int BoxAndSphere(Box& one, Sphere& two, CollisionData* data);
	static int BoxAndBox(Box& one, Box& two, CollisionData* data);
	static int BoxAndPoint(Box& one, Vector3& two, CollisionData* data);
	static int BoxAndPlane(Box& one, Plane& two, CollisionData* data);
};