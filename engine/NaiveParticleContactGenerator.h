#pragma once

#include "ParticleContactGenerator.h"

class NaiveParticleContactGenerator : public ParticleContactGenerator {

	float radius;

	std::vector<Particule*> particles;

	NaiveParticleContactGenerator();

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};