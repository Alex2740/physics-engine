#pragma once

#include "physics/Particule.h"
#include "core/math.h"

class ParticleContact
{
public:
	Particule* particules[2];
	float restitution;
	float penetration;
	Vector3 contactNormal;
	void resolve(float duration);
	float calculateSeparatingVelocity();

private : 
	void resolveVelocity();
	void resolveInterpenetration();
};