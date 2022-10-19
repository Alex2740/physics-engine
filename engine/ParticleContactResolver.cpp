#include "ParticleContactResolver.h"

ParticleContactResolver::ParticleContactResolver()
{
	iteration = 64;
}

ParticleContactResolver::ParticleContactResolver(unsigned int max_iteration)
{
	iteration = max_iteration;
}

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration)
{
	for (size_t i = 0; i < numContact; i++)
	{
		ParticleContact contact = contactArray[i];

		contact.resolve(duration);
	}
}
