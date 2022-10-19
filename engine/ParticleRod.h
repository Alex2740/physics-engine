#include "ParticleLink.h"

class ParticleRod : public ParticleLink {
public : 

	float length;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;


};