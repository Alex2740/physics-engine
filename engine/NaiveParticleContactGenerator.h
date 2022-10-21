#pragma once

#include "ParticleContactGenerator.h"

class NaiveParticleContactGenerator : public ParticleContactGenerator {

public:
	float radius;

	std::vector<Particule*> particles;

	NaiveParticleContactGenerator();

	unsigned int addContact(std::vector<ParticleContact*>& contact, unsigned int limit) const;
};