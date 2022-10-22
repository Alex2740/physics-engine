#include "WallContactGenerator.h"
#include <math.h>
#include "ParticleContact.h"

unsigned int WallContactGenerator::addContact(std::vector<ParticleContact*>& contact, unsigned int limit) const
{
	for (Particule* p : this->particules) {

		Vector3 realNormal = Vector3::Normalized(normal);

		float distance = Vector3::Dot(realNormal, p->position - origine);

		if (distance <= 0 && limit > 0) {
			
			ParticleContact* currentContact = new ParticleContact();
			currentContact->particules[0] = p;

			// Collision elastique (pas de perte de quantite de mouvement)
			currentContact->restitution = 1;

			currentContact->contactNormal = realNormal;
			currentContact->penetration = distance - particleRadius;

			contact.push_back(currentContact);
			limit--;
		}
	}

	return limit;
}
