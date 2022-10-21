#pragma once

#include "ParticleLink.h"

class ParticleRod : public ParticleLink {
public : 

	float length;


	ParticleRod(Particule* p1, Particule* p2, float length);

	unsigned int addContact(std::vector<ParticleContact*> &contact, unsigned int limit) const;


};