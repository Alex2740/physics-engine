#pragma once

#include "Vector3.h"

class IForceAppliable {
public:
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    float masse();
    float inverseMasse;
	float damping;

    virtual void integrate(Vector3 force, float dt);
};