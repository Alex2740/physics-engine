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
	contact.type = 0;
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
	contact.type = 1;

	contact.body[0] = one.body;
	contact.body[1] = nullptr;

	contact.contactNormal = two.normal;
	contact.contactPoint = one.body->position - two.normal * (distance + one.radius);
	contact.penetration = -distance;
	contact.friction; //TODO
	contact.restitution; // TODO

	data->AddContact(contact);
	return 1;
}

int CollisionDetector::SphereAndPlane(Sphere& one, Plane& two, CollisionData* data) {
	// Recuperation de la position de la sphere
	Vector3 spherePosition = one.offset * one.body->position;

	// Calcul de la distance entre la sphere et le plan
	float distance = Vector3::Dot(two.normal, spherePosition) - two.offset;
	
	if (std::abs(distance) > one.radius) {
		return 0;
	}

	if (data == nullptr) return 1;

	// Calcul de la normale et de la penetration
	Vector3 normal = two.normal;
	float penetration = -distance;

	if (distance < 0) {
		normal = normal * -1;
		penetration *= -1;
	}
	penetration += one.radius;

	// Creation du contact
	Contact contact;
	contact.type = 2;

	contact.body[0] = one.body;
	contact.body[1] = nullptr;

	contact.contactNormal = normal;
	contact.contactPoint = one.body->position - two.normal * distance;
	contact.penetration = penetration;
	contact.friction; //TODO
	contact.restitution; // TODO

	data->AddContact(contact);
	return 1;
}

int CollisionDetector::SphereAndPoint(Sphere& one, Vector3& two, CollisionData* data) {
	float distance = (one.body->position - two).getMagnitude();

	if (std::abs(distance) > one.radius) {
		return 0;
	}

	if (data == nullptr) return 1;

	Contact contact;
	contact.type = 3;

	contact.body[0] = one.body;
	contact.body[1] = nullptr;

	contact.contactNormal = Vector3::Normalized(one.body->position - two);
	contact.contactPoint = two;
	contact.penetration = one.radius - (one.body->position - two).getMagnitude();

	data->AddContact(contact);
	return 1;
}

int CollisionDetector::BoxAndHalfSpace(Box& one, Plane& two, CollisionData* data) {
	int contactCreated = 0;

	// Calcul de contact pour chaque sommet du cube
	for (auto vertice : one.getLocalCoordVertices())
	{
		// Recuperation de la distance entre le sommet et le plan
		float distance = Vector3::Dot(vertice,two.normal);

		// Creation du contact
		if (distance <= two.offset) {
			Contact contact;
			contact.type = 4;

			contact.body[0] = one.body;
			contact.body[1] = nullptr;

			contact.contactNormal = two.normal;
			contact.penetration = two.offset - distance;
			contact.contactPoint = vertice + two.normal * (distance - two.offset);
			contact.friction; //TODO
			contact.restitution; // TODO

			data->AddContact(contact);
			contactCreated++;
		}
	}
	
	return contactCreated;
}

int CollisionDetector::BoxAndSphere(Box& one, Sphere& two, CollisionData* data) {
	// Recupere la position de la sphere dans les coordonnes du cube
	Vector3 spherePosition = two.offset * two.body->position;
	Vector3 spherePosInCubeCoord = one.offset.transformInverse(spherePosition);

	if (std::abs(spherePosInCubeCoord.x) - two.radius > one.halfSize.x ||
		std::abs(spherePosInCubeCoord.y) - two.radius > one.halfSize.y ||
		std::abs(spherePosInCubeCoord.z) - two.radius > one.halfSize.z) {
		return 0;
	}

	// Calcul le point du cube le plus proche de la sphere
	Vector3 contactPointInCubeCoord = Vector3();
	if (spherePosInCubeCoord.x > one.halfSize.x) contactPointInCubeCoord.x = one.halfSize.x;
	if (spherePosInCubeCoord.x < -one.halfSize.x) contactPointInCubeCoord.x = -one.halfSize.x;

	if (spherePosInCubeCoord.y > one.halfSize.y) contactPointInCubeCoord.y = one.halfSize.y;
	if (spherePosInCubeCoord.y < -one.halfSize.y) contactPointInCubeCoord.y = -one.halfSize.y;

	if (spherePosInCubeCoord.z > one.halfSize.z) contactPointInCubeCoord.z = one.halfSize.z;
	if (spherePosInCubeCoord.z < -one.halfSize.z) contactPointInCubeCoord.z = -one.halfSize.z;

	// Calcul de la distance entre la sphere et le point du cube
	float distance = Vector3::Distance(contactPointInCubeCoord, spherePosInCubeCoord);
	if (distance > two.radius) return 0;

	Vector3 contactPoint = one.offset.transform(contactPointInCubeCoord);
	
	// Creation du contact
	Contact contact;
	contact.type = 5;

	contact.body[0] = one.body;
	contact.body[1] = two.body;
	contact.contactNormal = Vector3::Normalized(contactPoint - spherePosition);
	contact.contactPoint = contactPoint;
	contact.penetration = two.radius - distance;
	contact.friction; //TODO
	contact.restitution; // TODO

	data->AddContact(contact);
	return 1;
}

std::vector<Vector3> CollisionDetector::generateSATAllAxis(Box& one, Box& two)
{
	std::vector<Vector3> axis;

	// Generate axis from faces (6 axis)
	for (int i = 0; i < 3; i++)
	{
		axis.push_back(Vector3::Normalized(one.getAxis(i)));
		axis.push_back(Vector3::Normalized(two.getAxis(i)));
	}
	
	// Generate axis from edges (9 axis);
	for (int i = 0; i < 3; i++)
	{
		Vector3 edge1 = one.getAxis(i);
		for (int i = 0; i < 3; i++)
		{
			Vector3 edge2 = two.getAxis(i);

			axis.push_back(Vector3::Normalized(Vector3::Cross(edge1, edge2)));
		}
	}

	return std::vector<Vector3>();
}

Contact CollisionDetector::createContactPointFace(Box& face, Box& point, Vector3 axis, float interpenetration)
{
	Contact contact;

	Vector3 faceToPoint = face.body->position - point.body->position;

	// Get Face normal
	Vector3 normal = axis;
	if (Vector3::Dot(axis, faceToPoint) > 0) normal = normal * -1;

	// Get point
	Vector3 contactPoint = point.halfSize;
	if (Vector3::Dot(point.getAxis(0), normal) < 0) contactPoint.x = -contactPoint.x;
	if (Vector3::Dot(point.getAxis(1), normal) < 0) contactPoint.y = -contactPoint.y;
	if (Vector3::Dot(point.getAxis(2), normal) < 0) contactPoint.z = -contactPoint.z;

	// Transform local coord in world coord
	Vector3 contactPointInWorld = point.offset.transform(contactPoint);

	// Fill contact information
	contact.body[0] = face.body;
	contact.body[1] = point.body;
	contact.contactNormal = normal;
	contact.contactPoint = contactPointInWorld;
	contact.penetration = interpenetration;
	contact.friction; //TODO
	contact.restitution; // TODO

	return contact;
}

int CollisionDetector::BoxAndBox(Box& one, Box& two, CollisionData* data) 
{
	// Generate axis for SAT
	std::vector<Vector3> axis = CollisionDetector::generateSATAllAxis(one, two);
	
	int bestIndexAxis = -1;
	float bestInterpenetration = FP_INFINITE;

	// Calcul interpenetration on all axis
	for (int i = 0; i < axis.size(); i++)
	{
		auto axe = axis.at(i);
		float oneProjection = one.projectOnAxis(axe);
		float twoProjection = two.projectOnAxis(axe);

		float distance = Vector3::Dot(two.body->position - one.body->position, axe);
		float interpenetration = oneProjection + twoProjection - distance;

		if (interpenetration < 0) return 0;

		if (interpenetration < bestInterpenetration) {
			bestInterpenetration = interpenetration;
			bestIndexAxis = i;
		}
	}

	Contact contact;

	// Check contact type
	if (bestIndexAxis < 6) {
		// point-face
		if (bestIndexAxis % 2 == 0) {
			// point two-face one
			contact = createContactPointFace(two, one, axis.at(bestIndexAxis), bestInterpenetration);
		}
		else {
			// point one-face two
			contact = createContactPointFace(one, two, axis.at(bestIndexAxis), bestInterpenetration);
		}
	}
	else {
		// edge-edge

		// Get axis of contact
		int bestIndexAxisOnOne = (bestIndexAxis - 6) / 3;
		Vector3 axisOne = one.getAxis(bestIndexAxisOnOne);
		int bestIndexAxisOnTwo = (bestIndexAxis - 6) % 3;
		Vector3 axisTwo = two.getAxis(bestIndexAxisOnTwo);

		// Get contacts edges
		Vector3 middleEdgeOne = one.halfSize;
		Vector3 middleEdgeTwo = two.halfSize;
		for (int i = 0; i < 3; i++)
		{
			if (i == bestIndexAxisOnOne) middleEdgeOne.setAxis(i, 0);
			else if (Vector3::Dot(one.getAxis(i), axis.at(bestIndexAxis)) > 0) middleEdgeOne.setAxis(i, middleEdgeOne.getAxis(i) * -1);

			if (i == bestIndexAxisOnTwo) middleEdgeTwo.setAxis(i, 0);
			else if (Vector3::Dot(two.getAxis(i), axis.at(bestIndexAxis)) > 0) middleEdgeTwo.setAxis(i, middleEdgeTwo.getAxis(i) * -1);
		}

		// Transform edges local coords in wold coords
		middleEdgeOne = one.offset.transform(middleEdgeOne);
		middleEdgeTwo = two.offset.transform(middleEdgeTwo);

		// Calculate contact point
		Vector3 contactPoint;
		contactPoint.x = (middleEdgeOne.x + middleEdgeTwo.x) / 2;
		contactPoint.y = (middleEdgeOne.y + middleEdgeTwo.y) / 2;
		contactPoint.z = (middleEdgeOne.z + middleEdgeTwo.z) / 2;

		// Fill contact information
		contact.body[0] = one.body;
		contact.body[1] = two.body;
		contact.contactNormal = axis.at(bestIndexAxis);
		contact.contactPoint = contactPoint;
		contact.penetration = bestInterpenetration;
		contact.friction; //TODO
		contact.restitution; // TODO
	}

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
	float penetration = std::min({std::abs(one.halfSize.x) - std::abs(transformedPoint.x), std::abs(one.halfSize.y) - std::abs(transformedPoint.y), std::abs(one.halfSize.z) - std::abs(transformedPoint.z)});

	if (data == nullptr) return 1;

	Contact contact;
	contact.type = 7;
	contact.body[0] = one.body;
	contact.body[1] = nullptr;
	contact.penetration = penetration;
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
	contact.type = 8;
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
