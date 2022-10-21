#include "ParticleRod.h"
#include "ParticleLink.h"

ParticleRod::ParticleRod(Particule* p1, Particule* p2, float length) : ParticleLink(p1,p2)
{
	this->length = length;
}

unsigned int ParticleRod::addContact(ParticleContact* contact, unsigned int limit) const
{
	float currentLength = this->currentLength();
	int i = 0;
	while (contact[i] != nullptr) {
		i++;
	}

	// Si la distance est plus grande que la longueur de la tige, il y a contact
	if (currentLength > length) {

		ParticleContact* currentContact = new ParticleContact();
		// Pas sûr mais je pense que la restitution devrait être de 1 ?
		currentContact->restitution = 1;
		currentContact->penetration = 0;
		currentContact->particules = this->particle;
		currentContact->contactNormal = Vector3::Cross(this->particle[0], this->particle[1]);

		contact[i] = currentContact;

		return limit - 1;
	}
	// Sinon si elle est plus petite, il y a contact
	else if (currentLength < length) {

		ParticleContact* currentContact = new ParticleContact();
		// Pas sûr mais je pense que la restitution devrait être de 1 ?
		currentContact->restitution = 1;
		currentContact->penetration = 0;
		currentContact->particules = this->particle;

		// On inverse la normale
		currentContact->contactNormal = Vector3::Cross(this->particle[0], this->particle[1]) * -1;

		contact[i] = currentContact;


		return limit - 1;
	}
	// Sinon, pas de contact
	else {
		return limit;
	}

}
