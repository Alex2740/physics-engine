#pragma once

#include "ParticleLink.h"

class ParticleRod : public ParticleLink {
public : 

	float length;


	ParticleRod(Particule* p1, Particule* p2,foat length);

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;


};