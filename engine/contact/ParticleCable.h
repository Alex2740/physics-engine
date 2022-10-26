#pragma once

#include "ParticleLink.h"
#include "ParticleContact.h"
#include "Particule.h"


class ParticleCable : public ParticleLink {

public : 

	float maxLength;

	float restitution;


	ParticleCable(Particule* p1, Particule* p2, float maxLength, float restitution);
	unsigned int addContact(std::vector<ParticleContact*>& contact, unsigned int limit) const;

};