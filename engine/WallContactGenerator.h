#pragma once

#include "ParticleContactGenerator.h"
#include "Particule.h"

class WallContactGenerator : public ParticleContactGenerator{
public:
	float particleRadius;

	float a;
	float b;
	// droite d'équation y = ax + b

	int orientation = 1;
	// Orientation du mur

	std::vector<Particule*> particules;

	unsigned int addContact(std::vector<ParticleContact*>& contact, unsigned int limit) const;


};