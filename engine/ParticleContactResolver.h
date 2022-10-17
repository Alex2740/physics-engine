#pragma once
#include "ParticleContact.h"

class ParticleContactResolver
{
protected:
	// number of iteration allowed
	unsigned int iteration;

public:
	ParticleContactResolver();
	ParticleContactResolver(unsigned int max_iteration);

	void resolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration);
};
