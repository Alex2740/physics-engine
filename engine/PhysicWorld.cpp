#include "PhysicWorld.h"

PhysicWorld::PhysicWorld()
{
}

void PhysicWorld::AddParticule(Particule* particule)
{
	particules.push_back(particule);

	particuleRegistries[particule] = Registry::ParticuleRegistry(particule);
}

void PhysicWorld::DeleteParticule(Particule* particule)
{
}

void PhysicWorld::AddForce(Particule* particule, Force::Force* force)
{
	particuleRegistries[particule].addForce(force);
}

void PhysicWorld::DeleteForce(Particule* particule, Force::Force* force)
{
}

void PhysicWorld::RunPhysics(float duration)
{
	// Intégration des forces
	for (auto registry : particuleRegistries) {
		registry.second.update(duration);
	}

	// Détection des contacts

	// Résolution des contacts
	ParticleContact* contactArray = NULL;
	unsigned int numContact = 0;

	ParticleContactResolver resolver = ParticleContactResolver(numContact * 2);
	resolver.resolveContacts(contactArray, numContact, duration);
}
