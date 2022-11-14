#pragma once
#include "ParticleContact.h"
#include "physics/Registry.h"

class ParticleContactResolver
{
protected:
	// number of iteration allowed
	unsigned int iteration;

public:
	ParticleContactResolver();
	ParticleContactResolver(int max_iteration);

	void resolveContacts(std::map<Particule*, Registry::ParticuleRegistry> particuleRegistries, std::vector<ParticleContact*> contactArray, float duration);
};
