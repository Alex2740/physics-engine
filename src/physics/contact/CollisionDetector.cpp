#include "CollisionDetector.h"

int CollisionDetector::SphereAndSphere(Sphere& one, Sphere& two, CollisionData* data)
{
	// Teste s'il reste de la place dans le tableau des contacts
	// if (data->contactsLeft <= 0) return 1;

	// Récupération des positions des spheres
	Vector3 positionSphere1 = one.offset * one.body->position;
	Vector3 positionSphere2 = two.offset * two.body->position;

	Vector3 betweenSphere = positionSphere2 - positionSphere1;
	float distance = betweenSphere.getMagnitude();

	// Teste si les spheres sont en collision
	if (distance >= one.radius + two.radius) return 0;

	if (data == nullptr) return 1;

	Vector3 normal = Vector3::Normalized(betweenSphere);

	// Creation du contact
	Contact contact;
	contact.body[0] = one.body;
	contact.body[1] = two.body;
	contact.contactNormal = normal;
	contact.penetration = one.radius + two.radius - distance;
	contact.contactPoint = positionSphere1 + normal * (one.radius - (contact.penetration / 2));
	contact.friction; //TODO
	contact.restitution; // TODO

	data->AddContact(contact);
	
	return 1;
}

int CollisionDetector::SphereAndHalfSpace(Sphere& one, Plane& two, CollisionData* data) {
	
	Vector3 spherePosition = one.offset * one.body->position;
	
	float distance = Vector3::Dot(two.normal, spherePosition) - one.radius - two.offset;

	if (distance > 0) {
		return 0;
	}

	if (data == nullptr) return 1;

	Contact contact;
	contact.body[0] = one.body;
	contact.body[1] = nullptr;

	contact.contactNormal = two.normal;
	contact.contactPoint = one.body->position - two.normal * (distance + one.radius);
	contact.penetration = -distance;

	data->AddContact(contact);
	return 1;
}

int CollisionDetector::SphereAndPlane(Sphere& one, Plane& two, CollisionData* data) {
	Vector3 spherePosition = one.offset * one.body->position;

	float distance = Vector3::Dot(two.normal, spherePosition) - two.offset;
	
	if (std::abs(distance) > one.radius) {
		return 0;
	}

	if (data == nullptr) return 1;

	Vector3 normal = two.normal;
	float penetration = -distance;

	if (distance < 0) {
		normal = normal * -1;
		penetration *= -1;
	}
	penetration += one.radius;

	Contact contact;
	contact.body[0] = one.body;
	contact.body[1] = nullptr;

	contact.contactNormal = normal;
	contact.contactPoint = one.body->position - two.normal * distance;
	contact.penetration = penetration;

	data->AddContact(contact);
	return 1;
}

int CollisionDetector::BoxAndHalfSpace(Box& one, Plane& two, CollisionData* data) {
	int contactCreated = 0;

	for (auto vertice : one.getLocalCoordVertices())
	{
		float distance = Vector3::Dot(vertice,two.normal);

		if (distance <= two.offset) {
			Contact contact;
			contact.body[0] = one.body;
			contact.body[1] = nullptr;

			contact.contactNormal = two.normal;
			contact.penetration = two.offset - distance;
			contact.contactPoint = vertice + two.normal * (distance - two.offset);

			data->AddContact(contact);
			contactCreated++;
		}
	}
	
	return contactCreated;
}

int CollisionDetector::BoxAndSphere(Box& one, Sphere& two, CollisionData* data) {
	if ((one.body->position - two.body->position).getMagnitude() > (one.halfSize.getMagnitude() + two.radius)) {
		return 0;
	}

	bool isCollision = false;
	for (auto p: one.getLocalCoordVertices()) {
		if ((p - two.body->position).getMagnitude() < two.radius) {
			isCollision = true;
			break;
		}
	}

	if (!(isCollision)) return 0;

	if (data == nullptr) return 1;

	Contact contact;

	contact.body[0] = one.body;
	contact.body[1] = two.body;
	contact.contactNormal = Vector3::Normalized(one.body->position - two.body->position);

	data->AddContact(contact);
	return 1;
}

int CollisionDetector::BoxAndBox(Box& one, Box& two, CollisionData* data) {
	// first step: if the two boxes are enough far from each other, then no collision
	if ((one.body->position - two.body->position).getMagnitude() > (one.halfSize.getMagnitude() + two.halfSize.getMagnitude())) {
		return 0;
	}
	// otherwise I guess I have to test each point from one box, see if it's in the other
	bool isCollision = false;
	for (auto p: one.getLocalCoordVertices()) {
		if (CollisionDetector::BoxAndPoint(two, p, nullptr) != 0) {
			isCollision = true;
			break;
		} 
	}

	if (!(isCollision)) return 0;

	if (data == nullptr) return 1;

	Contact contact;
	contact.body[0] = one.body;
	contact.body[1] = two.body;

	contact.contactNormal = Vector3::Normalized(one.body->position - two.body->position);

	data->AddContact(contact);

	return 1;
}

int CollisionDetector::BoxAndPoint(Box& one, Vector3& two, CollisionData* data) {
	// first step: if it is outside the box,
	// 			   then surely no collision
	if (two.getMagnitude() > one.halfSize.getMagnitude()) {
		return 0;
	}
	// second step : do the projection on each plain of the cube,
	// see if the point fall into the projection range
	// to do this, we use the coordinate of cube, move the point
	// into this coordinate
	Matrix4 inverseTransformMat = one.offset.inverse();
	Vector3 transformedPoint = inverseTransformMat * two;
	if (!(std::abs(transformedPoint.x) < std::abs(one.halfSize.x)
	&&  std::abs(transformedPoint.y) < std::abs(one.halfSize.y)
	&&  std::abs(transformedPoint.z) < std::abs(one.halfSize.z)
	)) {
		// no collision if it is not in all the three projections
		return 0;
	}

	if (data == nullptr) return 1;

	Contact contact;
	contact.body[0] = one.body;
	contact.body[1] = nullptr;
	// TODO: check other data
	contact.contactNormal = Vector3::Zero();

	data->AddContact(contact);
	return 1;
}

int CollisionDetector::BoxAndPlane(Box& one, Plane& two, CollisionData* data) {
	// first step: get all the verties, so that I can test if any pair of vertices is crossing the plane "two"
	std::array<Vector3, 8> vertices = one.getLocalCoordVertices();
	std::vector<float> distances = std::vector<float>();
	// second step: for each vertex found, I can calculate their relative distance to the plain. The sign indicate on which side the vertex is found.
	for(Vector3 v: vertices) {
		distances.push_back(two.getDistanceToPoint(v));
	}
	std::sort(distances.begin(), distances.end());
	if (distances.at(0) * distances.at(7) > 0) {
		// every vertex at the same side; no collision
		return 0;
	}

	if (data == nullptr) return 1;

	// if there are two vertices on the different side, then collision

	// float penetration;
	// if (std::abs(distances.at(0)) > std::abs(distances.at(7))) {
	// 	penetration = -distances.at(0);
	// }
	// else {
	// 	penetration = distances.at(7);
	// }
	two.normal = Vector3::Normalized(two.normal);
	if (two.normal == Vector3::Zero()) {
		throw std::runtime_error("invalid normal value for plane");
	}
	
	Contact contact;
	contact.body[0] = one.body;
	contact.body[1] = nullptr; // TODO: check this
	contact.contactNormal = two.normal;
	contact.penetration = std::max(std::abs(distances.at(0)), std::abs(distances.at(7)));
	Vector3 cubeProjectionOnPlane = two.normal * two.offset + (one.body->position - Vector3::Cross(one.body->position, two.normal));
	// TODO: this needs some discussions
	contact.contactPoint = cubeProjectionOnPlane;
	contact.friction; //TODO
	contact.restitution; // TODO

	data->AddContact(contact);

	return 1;
}
