#include "ParticleContact.h"

void ParticleContact::resolve(float duration)
{
	resolveVelocity();
	resolveInterpenetration();
}

float ParticleContact::calculateSeparatingVelocity()
{
	Vector3 vrel = particules[0]->velocity;

	// Si la deuxième particule est un mur
	if (particules[1]) {
		vrel -= particules[1]->velocity;
	}

	return Vector3::Dot(vrel, contactNormal);
}

void ParticleContact::resolveVelocity()
{
	float separatingVelocity = calculateSeparatingVelocity();

	if (separatingVelocity > 0) return;

	float totalInverseMasse = particules[0]->inverseMasse;
	if (particules[1]) {
		totalInverseMasse += particules[1]->inverseMasse;
	}

	if (totalInverseMasse <= 0) return;

	float k = (restitution + 1) * separatingVelocity / totalInverseMasse;

	Vector3 impulse = contactNormal * k;

	particules[0]->velocity -= impulse * particules[0]->inverseMasse;

	if (particules[1]) {
		particules[1]->velocity += impulse * particules[1]->inverseMasse;
	}
}

void ParticleContact::resolveInterpenetration()
{
	if (penetration <= 0) return;

	float totalInverseMasse = particules[0]->inverseMasse;
	if (particules[1]) {
		totalInverseMasse += particules[1]->inverseMasse;
	}

	if (totalInverseMasse <= 0) return;

	Vector3 mouvements[2];

	mouvements[0] = contactNormal * particules[0]->inverseMasse * penetration / totalInverseMasse;

	if (particules[1]) {
		mouvements[1] = contactNormal * particules[1]->inverseMasse * penetration / totalInverseMasse;
	}
	else {
		mouvements[1] = Vector3::Zero();
	}
	
	particules[0]->position += mouvements[0];

	if (particules[1]) {
		particules[1]->position -= mouvements[1];
	}
}
