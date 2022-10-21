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

void PhysicWorld::AddParticleLink(ParticleLink* link) {
	this->contactGenerators.push_back(link);
}

void PhysicWorld::AddNaiveParticleGenerator(NaiveParticleContactGenerator* generator)
{
	this->contactGenerators.push_back(generator);
}

void PhysicWorld::RunPhysics(float duration)
{
	// Intégration des forces
	for (auto registry : particuleRegistries) {
		registry.second.update(duration);
	}

	// Détection des contacts

		// Résolution des contacts

	unsigned int numContact = 4;
	//ParticleContact contactArray[5];
	std::vector<ParticleContact*> contactArray;

	for (auto c : contactGenerators) {
		c->addContact(contactArray, numContact);
	}


	ParticleContactResolver resolver = ParticleContactResolver(numContact * 2);
	//resolver.resolveContacts(contactArray, numContact, duration);
}
