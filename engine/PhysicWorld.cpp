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
}
