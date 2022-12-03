#include "CollisionDetector.h"

int CollisionDetector::SphereAndSphere(Sphere& one, Sphere& two, CollisionData* data)
{
	// Teste s'il reste de la place dans le tableau des contacts
	if (data->contactsLeft <= 0) return 0;

	// Récupération des positions des spheres
	Vector3 positionSphere1 = one.offset * one.body->position;
	Vector3 positionSphere2 = two.offset * two.body->position;

	Vector3 betweenSphere = positionSphere2 - positionSphere1;
	float distance = betweenSphere.getMagnitude();

	// Teste si les spheres sont en collision
	if (distance >= one.radius + two.radius) return 0;

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
