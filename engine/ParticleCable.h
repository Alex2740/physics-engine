#include "ParticleLink.h"

class ParticleCable : public ParticleLink {

public : 

	float maxLength;

	float restitution;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;

};