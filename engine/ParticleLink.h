#pragma once

#include "ParticleContactGenerator.h"
#include "Particule.h"
#include "ParticleContact.h"

class ParticleLink : public ParticleContactGenerator {

public : 

	Particule* particle[2];

	float currentLength() const;

	ParticleLink(Particule* p1, Particule* p2);

	unsigned int addContact(std::vector<ParticleContact*>& contact, unsigned int limit) const = 0;

};