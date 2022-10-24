#include "ParticleContactResolver.h"

ParticleContactResolver::ParticleContactResolver()
{
	iteration = 64;
}

ParticleContactResolver::ParticleContactResolver(unsigned int max_iteration)
{
	iteration = max_iteration;
}

void ParticleContactResolver::resolveContacts(std::map<Particule*, Registry::ParticuleRegistry> particuleRegistries, std::vector<ParticleContact*> contactArray, float duration)
{
	while (iteration > 0) {
		float min = INFINITY;
		unsigned index = -1;

		for (int i = 0; i < contactArray.size(); i++)
		{
			float separatingVelocity = contactArray[i]->calculateSeparatingVelocity();

			if (separatingVelocity < min) {
				if (separatingVelocity < 0 || contactArray[i]->penetration > 0) {
					min = separatingVelocity;
					index = i;
				}
			}
		}

		if (index == -1) break;

		contactArray[index]->resolve(duration);

		// Contact au repos
		Particule** particules = contactArray[index]->particules;

		// Particule 1
		Vector3 gravity1 = particuleRegistries[particules[0]].getGravityForce();

		if ((gravity1 * duration).getMagnitude() > particules[0]->velocity.getMagnitude()) {
			particules[0]->velocity -= Vector3::Project(particules[0]->velocity, contactArray[index]->contactNormal);
		}

		// Particule 2
		if (particules[1]) {
			Vector3 gravity2 = particuleRegistries[particules[1]].getGravityForce();

			if ((gravity2 * duration).getMagnitude() > particules[1]->velocity.getMagnitude()) {
				particules[0]->velocity -= Vector3::Project(particules[1]->velocity, contactArray[index]->contactNormal);
			}
		}

		iteration--;
	}
}
