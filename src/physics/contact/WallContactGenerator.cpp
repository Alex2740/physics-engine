#include "WallContactGenerator.h"

#include <math.h>

WallContactGenerator::WallContactGenerator(std::vector<Particule*> particules, Vector3 normal, Vector3 origine, float wallRadius)
{
	this->particules = particules;
	this->normal = Vector3::Normalized(normal);
	this->origine = origine;
	this->wallRadius = wallRadius;

	if (this->normal == Vector3::Zero()) {
		throw std::runtime_error("invalid \"normal\" value");
	}
}

unsigned int WallContactGenerator::addContact(std::vector<ParticleContact*>& contact, unsigned int limit)
{
	for (Particule* p : this->particules) {

		float distance = Vector3::Dot(normal, p->position - origine) - wallRadius;

		if (distance <= 0) {
			
			ParticleContact* currentContact = new ParticleContact(); //TODO check if it's freed later
			currentContact->particules[0] = p;

			// Collision elastique (pas de perte de quantite de mouvement)
			currentContact->restitution = 1;

			currentContact->contactNormal = normal;
			currentContact->penetration = distance;

			contact.push_back(currentContact);

			limit--;
			if (limit == 0) break; // a break is more efficient here
		}
	}

	return limit;
}
