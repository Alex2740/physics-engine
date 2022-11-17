#pragma once

#include "core/Vector3.h"

class IForceAppliable {
public:
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    float masse();
    float inverseMasse;
	float damping;

    virtual void integrate(float dt) = 0;
};