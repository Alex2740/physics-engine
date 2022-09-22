#pragma once

#include <math.h>

#include "Vector3.h"

class Particule
{
private:
	float inverseMasse_ = 0;
	float damping_ = 0.999f;

public:
	Vector3* position;
	Vector3* velocity;
	Vector3* acceleration;
	
	const float& inverseMasse = inverseMasse_;
	const float& damping = damping_;

	Particule();
	Particule(Vector3* _position, float _masse);
	Particule(Vector3* _position, float _masse, float _damping);

	void setMasse(float _masse);
	void setInverseMasse(float _inverseMasse);

	float masse();

	//void integrate(Vector3* forces, float dt);
	void integrate(Vector3* forces, float dt);
};