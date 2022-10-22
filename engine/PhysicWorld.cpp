#include "PhysicWorld.h"

PhysicWorld::PhysicWorld()
{
}

void PhysicWorld::AddParticule(Particule* particle)
{
	particules.push_back(particle);
	particuleRegistries[particle] = Registry::ParticuleRegistry(particle);
}

void PhysicWorld::DeleteParticule(Particule* particle)
{
	particuleRegistries.erase(particle);
}

void PhysicWorld::AddForce(Particule* particle, Force::Force* force)
{
	particuleRegistries[particle].addForce(force);
}

void PhysicWorld::DeleteForce(Particule* particle, Force::Force* force)
{
	particuleRegistries[particle].delForce(force);
}

void PhysicWorld::AddParticleLink(ParticleLink* link) {
	contactGenerators.push_back(link);
}

void PhysicWorld::AddNaiveParticleGenerator(NaiveParticleContactGenerator* generator)
{
	contactGenerators.push_back(generator);
}

void PhysicWorld::AddWallContactGenerator(WallContactGenerator* generator)
{
	contactGenerators.push_back(generator);
}

void PhysicWorld::RunPhysics(float duration)
{
	// Intégration des forces
	for (auto registry : particuleRegistries) {
		registry.second.update(duration);
	}

	// Détection des contacts
	unsigned int limitContact = 2048;
	std::vector<ParticleContact*> contactArray;

	for (auto c : contactGenerators) {
		c->addContact(contactArray, limitContact);
	}

	// Résolution des contacts
	ParticleContactResolver resolver = ParticleContactResolver(contactArray.size() * 2);
	resolver.resolveContacts(this->particuleRegistries, contactArray, duration);
}
