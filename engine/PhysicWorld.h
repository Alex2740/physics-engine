#pragma once

#include "Particule.h"
#include "Force.h"
#include "ParticleContactResolver.h"
#include "ParticleContact.h"

class PhysicWorld
{
private:
	std::vector<Particule*> particules;
	std::map<Particule*, Registry::ParticuleRegistry> particuleRegistries;

public:
	PhysicWorld();

	void AddParticule(Particule* particule);
	void DeleteParticule(Particule* particule);

	void AddForce(Particule* particule, Force::Force* force);
	void DeleteForce(Particule* particule, Force::Force* force);

	void RunPhysics(float duration);
};