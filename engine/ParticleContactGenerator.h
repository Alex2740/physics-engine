#include "ParticleContact.h"

class ParticleContactGenerator {

	virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;

};