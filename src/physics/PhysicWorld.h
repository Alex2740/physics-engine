#pragma once

#include "Particule.h"
#include "Force.h"
#include "Registry.h"
#include "Rigidbody.h"
#include "contact/ParticleContactResolver.h"
#include "contact/ParticleContact.h"
#include "contact/ParticleLink.h"
#include "contact/ParticleContactGenerator.h"
#include "contact/NaiveParticleContactGenerator.h"
#include "contact/WallContactGenerator.h"
#include "contact/BVHNode.h"

#include <stdlib.h>

#define CONTACT_LIMIT 10

class PhysicWorld
{
private:
	std::vector<Particule*> particules;
	std::vector<RigidBody*> rigidBodies;
	std::map<Particule*, Registry::ParticuleRegistry> particuleRegistries;
	std::map<RigidBody*, Registry::RigidRegistry> rigidBodyRegistries;
	std::vector<ParticleContactGenerator*> contactGenerators;

public:
	PhysicWorld();
	~PhysicWorld();

	void AddParticule(Particule* particule);
	void DeleteParticule(Particule* particule);

	void AddRigidBody(RigidBody* rb);
	void DeleteRigidBody(RigidBody* rb);

	void AddForce(Particule* particule, Force::Force* force);
	void DeleteForce(Particule* particule, Force::Force* force);

	void AddForce(RigidBody* rb, Force::Force* f);
	void AddForceLocalPoint(RigidBody* rb, Force::Force* f, Vector3 coord);
	void AddForceWorldPoint(RigidBody* rb, Force::Force* f, Vector3 coord);

	void AddContactGenerator(ParticleContactGenerator* generator);
	
	static PotentialContact** BroadPhase(BVHNode* root);

	void RunPhysics(float duration);
};