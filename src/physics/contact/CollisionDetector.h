#pragma once

#include "primitive/Sphere.h"
#include "primitive/Plane.h"
#include "primitive/Box.h"
#include "CollisionData.h"

#include <vector>
#include <algorithm> 
#include <cmath>
#include <limits>

class CollisionDetector
{
public:
	static int SphereAndSphere(Sphere& one, Sphere& two, CollisionData* data);
	static int SphereAndHalfSpace(Sphere& one, Plane& two, CollisionData* data);
	static int SphereAndPlane(Sphere& one, Plane& two, CollisionData* data);
	static int BoxAndHalfSpace(Box& one, Plane& two, CollisionData* data);
	static int BoxAndSphere(Box& one, Sphere& two, CollisionData* data);
	static int BoxAndBox(Box& one, Box& two, CollisionData* data);
	static int BoxAndPoint(Box& one, Vector3& two, CollisionData* data);
	static int BoxAndPlane(Box& one, Plane& two, CollisionData* data);
};