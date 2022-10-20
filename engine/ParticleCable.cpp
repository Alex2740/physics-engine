#include "ParticleCable.h"
#include "ParticleLink.h"
#include "Vector3.h"
#include <st>

ParticleCable::ParticleCable(Particule* particules, float maxLength, float restitution) : ParticleLink(particules)
{
	this->maxLength = maxLength;
	this->restitution = restitution;
}

unsigned int ParticleCable::addContact(ParticleContact* contact, unsigned int limit) const
{
	float currentLength = this->currentLength();

	// Si la distance entre les 2 particules est inférieure à la distance max du cable, pas de contact
	if (currentLength < this->maxLength) {
		return limit;
	}
	//Sinon il y a contact
	else {

		ParticleContact* currentContact = new ParticleContact();
		currentContact->particules = this->particle;
		currentContact->restitution = this->restitution;
		currentContact->penetration = 0;
		currentContact->contactNormal = Vector3::Cross(this->particle[0], this->particle[1]);

		int i = 0;
		while (contact[i] != nullptr) {
			i++;
		}

		contact[i] = currentContact;

		return limit - 1;
	}
}

