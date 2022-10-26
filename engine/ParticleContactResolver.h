#pragma once
#include "ParticleContact.h"
#include "Registry.h"

class ParticleContactResolver
{
protected:
	// number of iteration allowed
	unsigned int iteration;

public:
	ParticleContactResolver();
	ParticleContactResolver(unsigned long max_iteration);

	void resolveContacts(std::map<Particule*, Registry::ParticuleRegistry> particuleRegistries, std::vector<ParticleContact*> contactArray, float duration);
};
