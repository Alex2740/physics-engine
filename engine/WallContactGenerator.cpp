#include "WallContactGenerator.h"
#include <math.h>
#include "ParticleContact.h"

unsigned int WallContactGenerator::addContact(std::vector<ParticleContact*>& contact, unsigned int limit) const
{
	for (Particule* p : this->particules) {
		
		float num = this->a * p->position.x - p->position.y + this->b;
		float denom = sqrt(this->a * this->a + 1);

		float distance = num / denom;

		if (distance*this->orientation <= 0 && limit > 0) {
			
			ParticleContact* currentContact = new ParticleContact();
			currentContact->particules[0] = p;

			// Collision elastique (pas de perte de quantite de mouvement)
			currentContact->restitution = 1;

			contact.push_back(currentContact);
			limit--;
		}
	}


	return limit;
}
