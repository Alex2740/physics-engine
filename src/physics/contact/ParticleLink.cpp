#include "ParticleLink.h"
#include "core/math.h"

ParticleLink::ParticleLink(Particule* p1, Particule* p2) {
	this->particle[0] = p1;
	this->particle[1] = p2;
}

float ParticleLink::currentLength() const {
	return Vector3::Distance(this->particle[0]->position, this->particle[1]->position);
}

