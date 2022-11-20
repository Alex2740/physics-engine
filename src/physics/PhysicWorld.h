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

	void AddContactGenerator(ParticleContactGenerator* generator);
	

	void RunPhysics(float duration);
};