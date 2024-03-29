#pragma once

#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator {

public : 

	Particule* particle[2];

	float currentLength() const;

	ParticleLink(Particule* p1, Particule* p2);

	virtual unsigned int addContact(std::vector<ParticleContact*>& contact, unsigned int limit) = 0;

};