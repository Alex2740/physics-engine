#include "PhysicWorld.h"

PhysicWorld::PhysicWorld()
{
}

PhysicWorld::~PhysicWorld()
{
	// clear up memories
	for (auto p: this->particuleRegistries) {
		p.second.free();
	}

	for (auto p : this->rigidBodyRegistries) {
		p.second.free();
	}

	for (auto p: this->contactGenerators) {
		delete p;
	}
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

void PhysicWorld::AddRigidBody(RigidBody* rb)
{
	rigidBodies.push_back(rb);
	rigidBodyRegistries[rb] = Registry::RigidRegistry(rb);
}

void PhysicWorld::DeleteRigidBody(RigidBody* rb)
{
	rigidBodyRegistries.erase(rb);
}

void PhysicWorld::AddForce(Particule* particle, Force::Force* force)
{
	particuleRegistries[particle].addForce(force);
}

void PhysicWorld::DeleteForce(Particule* particle, Force::Force* force)
{
	particuleRegistries[particle].delForce(force);
}

void PhysicWorld::AddForce(RigidBody* rb, Force::Force* f)
{
	rigidBodyRegistries[rb].addForce(f);
}

void PhysicWorld::AddForceLocalPoint(RigidBody* rb, Force::Force* f, Vector3 coord)
{
	rigidBodyRegistries[rb].addForceLocalPoint(f, coord);
}

void PhysicWorld::AddForceWorldPoint(RigidBody* rb, Force::Force* f, Vector3 coord)
{
	rigidBodyRegistries[rb].addForceWorldPoint(f, coord);
}



void PhysicWorld::AddContactGenerator(ParticleContactGenerator* generator)
{
	contactGenerators.push_back(generator);
}

void PhysicWorld::RunPhysics(float duration)
{
	// Intégration des forces particules
	for (auto registry : particuleRegistries) {
		registry.second.update(duration);
	}


	// Intégration des forces rigidbodies
	for (auto registry : rigidBodyRegistries) {
		registry.second.update(duration);
	}

	// Détection des contacts
	unsigned int limitContact = 2048;
	std::vector<ParticleContact*> contactArray;

	for (auto c : contactGenerators) {
		c->addContact(contactArray, limitContact);
	}

	// Résolution des contacts
	ParticleContactResolver resolver = ParticleContactResolver(static_cast<int>(contactArray.size()) * 2);
	resolver.resolveContacts(this->particuleRegistries, contactArray, duration);

	for (auto cp: contactArray) {
		delete cp;
	}
}

void PhysicWorld::BroadPhase(BVHNode* root) {
	// Si c'est une feuille il n'y a pas de noeud fils qui peuvent entrer en collision
	if (root->isLeaf()) {
		return;
	}
	else {
		PotentialContact* contacts = new PotentialContact();
		root->getPotentialContacts(contacts, 10);

		if (contacts->bodies[0] != NULL && contacts->bodies[1] != NULL) {
			std::cout << "Contact possible entre " << contacts->bodies[0]->getId() << " et " << contacts->bodies[1]->getId() << std::endl;
		}

		BroadPhase(root->getLeftChildren());

		BroadPhase(root->getRightChildren());
	}

}
