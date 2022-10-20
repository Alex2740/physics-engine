#include "ParticleContactGenerator.h"
#include "Particule.h"
#include "ParticleContact.h"

class ParticleLink : public ParticleContactGenerator {

public : 

	Particule* particle[2];

	float currentLength() const;

	ParticleLink(Particule* particules);

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;

};