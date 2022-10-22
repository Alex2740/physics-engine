#pragma once

#include "ParticleContactGenerator.h"
#include "Particule.h"

class WallContactGenerator : public ParticleContactGenerator{
public:
	float particleRadius;

	Vector3 normal;
	Vector3 origine;

	std::vector<Particule*> particules;

	unsigned int addContact(std::vector<ParticleContact*>& contact, unsigned int limit) const;


};