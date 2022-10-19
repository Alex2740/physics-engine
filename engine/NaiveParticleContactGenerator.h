#include "ParticleContactGenerator.h"

class NaiveParticleContactGenerator : public ParticleContactGenerator {

	float radius;

	std::vector<Particule*> particles;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};