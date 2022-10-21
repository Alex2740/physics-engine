#include "ParticleContactResolver.h"

ParticleContactResolver::ParticleContactResolver()
{
	iteration = 64;
}

ParticleContactResolver::ParticleContactResolver(unsigned int max_iteration)
{
	iteration = max_iteration;
}

void ParticleContactResolver::resolveContacts(std::map<Particule*, Registry::ParticuleRegistry> particuleRegistries, std::vector<ParticleContact*> contactArray, unsigned int numContact, float duration)
{
	for (auto contact: contactArray)
	{
		// ParticleContact contact = *contactArray.at(i);

		contact->resolve(duration);
	}
	for (auto contact: contactArray)
	{
		Particule** particule = contact->particules;
		// Particule 1
		Vector3 gravity1 = particuleRegistries[particule[0]].getGravityForce();

		if ((gravity1 * duration).magnitude > particule[0]->velocity.magnitude) {
			particule[0]->velocity -= Vector3::Project(particule[0]->velocity, contact->contactNormal);
		}


		// Particule 2
		Vector3 gravity2 = particuleRegistries[particule[1]].getGravityForce();

		if ((gravity2 * duration).magnitude > particule[1]->velocity.magnitude) {
			particule[0]->velocity -= Vector3::Project(particule[1]->velocity, contact->contactNormal);
		}
	}
}
