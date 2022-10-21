#include "ParticleCable.h"
#include "Vector3.h"
#include <stdio.h>


ParticleCable::ParticleCable(Particule* p1, Particule* p2, float maxLength, float restitution) : ParticleLink(p1, p2)
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
		currentContact->particules[0] = this->particle[0];
		currentContact->particules[1] = this->particle[1];
		currentContact->restitution = this->restitution;
		currentContact->penetration = 0;
		currentContact->contactNormal = Vector3::Cross(this->particle[0]->position, this->particle[1]->position);

		int i = 0;
		while (&contact[i] != nullptr) {
			i++;
		}

		std::cout << "Contact cable" << std::endl;

		contact[i] = *currentContact;

		return limit - 1;
	}
}

