#include "NaiveParticleContactGenerator.h"
#include "Vector3.h"


NaiveParticleContactGenerator::NaiveParticleContactGenerator(std::vector<Particule*> particles, float particleRadius)
{
	this->particles = particles;
	this->radius = particleRadius;
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

				// Collision elastique (pas de perte de quantite de mouvement)
				currentContact->restitution = 1;
		
				currentContact->contactNormal = Vector3::Normalized(particles[i]->position - particles[j]->position);
				currentContact->penetration = -(distance - 2 * radius);

				contact.push_back(currentContact);

				limit--;
			}
		}
	}
	
	return limit;
}
