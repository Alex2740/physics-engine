#include "NaiveParticleContactGenerator.h"
#include "Vector3.h"

NaiveParticleContactGenerator::NaiveParticleContactGenerator() {

}

unsigned int NaiveParticleContactGenerator::addContact(std::vector<ParticleContact*>& contact, unsigned int limit) const
{

	// On it�re sur les paires de particules
	// On ne rev�rifie pas 2 fois la m�me paire
	for (int i = 0; i < particles.size(); i++) {
		for (int j = i + 1; j < particles.size(); j++) {
			
			float distance = Vector3::Distance(particles[i]->position, particles[j]->position);
			
			// Si les particule se touchent (ou si interpenetration), contact
			if (distance <= 2 * radius && limit > 0) {

				ParticleContact* currentContact = new ParticleContact();
				
				currentContact->particules[0] = particles[i];
				currentContact->particules[1] = particles[j];

				// Collision elastique (pas de perte de quantite de mouvement)
				currentContact->restitution = 1;
		
				currentContact->contactNormal = particles[j]->position - particles[i]->position;
				currentContact->penetration = Vector3::Dot(particles[i]->position - particles[j]->position, currentContact->contactNormal);

				contact.push_back(currentContact);

				limit--;
			}
		}
	}
	
	return limit;
}
