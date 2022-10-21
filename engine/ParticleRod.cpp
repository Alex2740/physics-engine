#include "ParticleRod.h"
#include "ParticleLink.h"

ParticleRod::ParticleRod(Particule* p1, Particule* p2, float length) : ParticleLink(p1,p2)
{
	this->length = length;
}

unsigned int ParticleRod::addContact(std::vector<ParticleContact*>& contact, unsigned int limit) const
{
	float currentLength = this->currentLength();

	// Si la distance est plus grande que la longueur de la tige, il y a contact
	if (currentLength > length) {

		ParticleContact* currentContact = new ParticleContact();
		// Pas sûr mais je pense que la restitution devrait être de 1 ?
		currentContact->restitution = 1;
		currentContact->penetration = 0;
		currentContact->particules[0] = this->particle[0];
		currentContact->particules[1] = this->particle[1];
		currentContact->contactNormal = Vector3::Cross(this->particle[0]->position, this->particle[1]->position);
		
		contact.push_back(currentContact);
		
		return limit - 1;
	}
	// Sinon si elle est plus petite, il y a contact
	else if (currentLength < length) {

		ParticleContact* currentContact = new ParticleContact();
		// Pas sûr mais je pense que la restitution devrait être de 1 ?
		currentContact->restitution = 1;
		currentContact->penetration = 0;
		currentContact->particules[0] = this->particle[0];
		currentContact->particules[1] = this->particle[1];

		// On inverse la normale
		currentContact->contactNormal = Vector3::Cross(this->particle[0]->position, this->particle[1]->position) * -1;

		contact.push_back(currentContact);
		

		return limit - 1;
	}
	// Sinon, pas de contact
	else {
		return limit;
	}

}
