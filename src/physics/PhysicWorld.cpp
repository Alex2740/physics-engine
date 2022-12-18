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

std::vector<RigidBody*> PhysicWorld::GetRigidBodies()
{
	return rigidBodies;
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
	rigidBodies.erase(std::remove(rigidBodies.begin(), rigidBodies.end(), rb), rigidBodies.end());
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

void PhysicWorld::RunPhysicsParticule(float duration)
{
	// Intégration des forces particules
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
	ParticleContactResolver resolver = ParticleContactResolver(static_cast<int>(contactArray.size()) * 2);
	resolver.resolveContacts(this->particuleRegistries, contactArray, duration);

	for (auto cp: contactArray) {
		delete cp;
	}
}

void PhysicWorld::RunPhysics(float duration)
{
	// Intégration des forces rigidbodies
	for (auto registry : rigidBodyRegistries) {
		registry.second.update(duration);
	}

	// Détection des contacts

	// Broad Phase

	// Construction du BVH
	size_t rbCount = rigidBodies.size();
	if (rbCount == 0) return;

	BVHNode* root = new BVHNode(nullptr, rigidBodies.at(0)->createBoundingSphere(), rigidBodies.at(0));

	if (rbCount == 1) return;

	for (int i = 1; i < rbCount; i++)
	{
		root->insert(rigidBodies.at(i), rigidBodies.at(i)->createBoundingSphere());
	}

	/*root->print();
	std::cout << "\n";*/

	auto listPotentialContact = PhysicWorld::BroadPhase(root);

	/*for each (PotentialContact pc in list)
	{
		std::cout << "body1: " << pc.bodies[0]->getId();
		std::cout << "\nbody2: " << pc.bodies[1]->getId();
		std::cout << std::endl;
	}

	std::cout << "-------" << std::endl;*/

	delete root;

	// Narrow Phase
	CollisionData data = PhysicWorld::NarrowPhase(listPotentialContact);

	if (data.getContactList().size() > 0) {
		system("pause");
	}
}

std::vector<PotentialContact> PhysicWorld::BroadPhase(BVHNode* root) {
	// Si c'est une feuille il n'y a pas de noeud fils qui peuvent entrer en collision
	if (root->isLeaf()) {
		return std::vector<PotentialContact>();
	}
	else {
		std::vector<PotentialContact> potentialContacts = std::vector<PotentialContact>();

		// if (contacts->bodies[0] != NULL && contacts->bodies[1] != NULL) {
		// 	std::cout << "Contact possible entre " << contacts->bodies[0]->getId() << " et " << contacts->bodies[1]->getId() << std::endl;
		// }

		std::vector<PotentialContact> rootPC = root->getPotentialContacts();
		potentialContacts.insert(potentialContacts.end(), rootPC.begin(), rootPC.end());

		std::vector<PotentialContact> leftPC = BroadPhase(root->getLeftChildren());
		potentialContacts.insert(potentialContacts.end(), leftPC.begin(), leftPC.end());

		std::vector<PotentialContact> rightPC = BroadPhase(root->getRightChildren());
		potentialContacts.insert(potentialContacts.end(), rightPC.begin(), rightPC.end());

		return potentialContacts;
	}
}

CollisionData PhysicWorld::NarrowPhase(std::vector<PotentialContact> potentialContacts)
{
	CollisionData data = CollisionData();

	CollisionDetector::detectList(potentialContacts, &data);
	
	return data;
}
