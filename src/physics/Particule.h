#pragma once

#include <vector>
#include <map>
#include <cmath>

#include "IForceAppliable.h"
#include "core/math.h"

class Particule : public IForceAppliable
{

public:
	// Vector3 position = Vector3::Zero();
	// Vector3 velocity = Vector3::Zero();
	// Vector3 acceleration = Vector3::Zero();

	Particule();
	Particule(Vector3 _position, float _masse);
	Particule(Vector3 _position, float _masse, float _damping);

	Particule operator=(const Particule& other);
	bool operator==(const Particule& other);
	bool operator!=(const Particule& other);

	void setMasse(float _masse);
	void setInverseMasse(float _inverseMasse);

	float masse();

	void integrate(Vector3 forces, float dt);
};