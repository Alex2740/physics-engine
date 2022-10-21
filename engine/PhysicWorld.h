#pragma once

#include "Particule.h"
#include "Force.h"
#include "Registry.h"
#include "ParticleContactResolver.h"
#include "ParticleContact.h"
#include "ParticleLink.h"
#include "ParticleContactGenerator.h"

class PhysicWorld
{
private:
	std::vector<Particule*> particules;
	std::map<Particule*, Registry::ParticuleRegistry> particuleRegistries;
	std::vector<ParticleContactGenerator*> contactGenerators;

public:
	PhysicWorld();

	void AddParticule(Particule* particule);
	void DeleteParticule(Particule* particule);

	void AddForce(Particule* particule, Force::Force* force);
	void DeleteForce(Particule* particule, Force::Force* force);

	void AddParticleLink(ParticleLink* link);

	void RunPhysics(float duration);
};