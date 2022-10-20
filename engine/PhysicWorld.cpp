#include "PhysicWorld.h"

PhysicWorld::PhysicWorld()
{
}

void PhysicWorld::AddParticule(Particule* particle)
{
	particleRegistries[particle] = Registry::ParticuleRegistry(particle);
}

void PhysicWorld::DeleteParticule(Particule* particle)
{
	particleRegistries.erase(particle);
}

void PhysicWorld::AddForce(Particule* particle, Force::Force* force)
{
	particleRegistries[particle].addForce(force);
}

void PhysicWorld::DeleteForce(Particule* particle, Force::Force* force)
{
	particleRegistries[particle].delForce(force);
}

void PhysicWorld::RunPhysics(float duration)
{
	// Intégration des forces
	for (auto registry : particleRegistries) {
		registry.second.update(duration);
	}

	// Détection des contacts

	// Résolution des contacts
	ParticleContact* contactArray = NULL;
	unsigned int numContact = 0;

	ParticleContactResolver resolver = ParticleContactResolver(numContact * 2);
	resolver.resolveContacts(contactArray, numContact, duration);

	// Résolution des contacts au repos
	for (size_t i = 0; i < numContact; i++)
	{
		Particule** particule = contactArray[i].particules;
		// Particule 1
		Vector3 gravity1 = particleRegistries[particule[0]].getGravityForce();

		if ((gravity1 * duration).magnitude > particule[0]->velocity.magnitude) {
			particule[0]->velocity -= Vector3::Project(particule[0]->velocity, contactArray[i].contactNormal);
		}


		// Particule 2
		Vector3 gravity2 = particleRegistries[particule[1]].getGravityForce();

		if ((gravity2 * duration).magnitude > particule[1]->velocity.magnitude) {
			particule[0]->velocity -= Vector3::Project(particule[1]->velocity, contactArray[i].contactNormal);
		}
	}
}
