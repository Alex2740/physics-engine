#include "ParticleLink.h"
#include "Vector3.h"

ParticleLink::ParticleLink(Particule* particules) {
	this->particle = particules;
}

float ParticleLink::currentLength() const {
	return Vector3::Distance(this->particle[0], this->particle[1]);
}

