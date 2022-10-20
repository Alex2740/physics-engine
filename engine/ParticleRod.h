#include "ParticleLink.h"

class ParticleRod : public ParticleLink {
public : 

	float length;


	ParticleRod(Particule* particules, float length);

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;


};