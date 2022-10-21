#include "NaiveParticleContactGenerator.h"
#include "Vector3.h"

NaiveParticleContactGenerator::NaiveParticleContactGenerator() {

}

unsigned int NaiveParticleContactGenerator::addContact(std::vector<ParticleContact*>& contact, unsigned int limit) const
{

	// On itère sur les paires de particules
	// On ne revérifie pas 2 fois la même paire
	for (int i = 0; i < particles.size(); i++) {
		for (int j = i + 1; j < particles.size(); j++) {
			
			float distance = Vector3::Distance(particles[i]->position, particles[j]->position);
			

			// Si les particule se touchent (ou si interpenetration), contact
			if (distance <= 2 * radius && limit > 0) {

				ParticleContact* currentContact = new ParticleContact();
				
				currentContact->particules[0] = particles[i];
				currentContact->particules[1] = particles[j];

				// jsp quelle valeur faut mettre
				currentContact->restitution = 1;
				// A modifier, pas sûr de la formule
				currentContact->penetration = 0;
				currentContact->contactNormal = Vector3::Cross(particles[i]->position, particles[j]->position);

				
				contact.push_back(currentContact);

				limit--;
			}

		}
	}
	
	return limit;
}
