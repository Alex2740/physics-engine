#include "ParticleContact.h"

void ParticleContact::resolve(float duration)
{
	resolveVelocity();
	resolveInterpenetration();
}

float ParticleContact::calculateSeparatingVelocity()
{
	return 0.0f;
}

void ParticleContact::resolveVelocity()
{
	Vector3 n = Vector3::Normalized(particules[0]->velocity);
	Vector3 vrel = particules[0]->velocity - particules[1]->velocity;
	float k = ((restitution + 1) * Vector3::Dot(vrel, n)) / ((particules[0]->inverseMasse + particules[1]->inverseMasse) * Vector3::Dot(n, n));

	particules[0]->velocity -= n * k * particules[0]->inverseMasse;
	particules[1]->velocity += n * k * particules[1]->inverseMasse;
}

void ParticleContact::resolveInterpenetration()
{
	float totalMasse = particules[0]->masse() + particules[1]->masse();

	particules[0]->position += contactNormal * particules[1]->masse() / totalMasse * penetration;
	particules[1]->position -= contactNormal * particules[0]->masse() / totalMasse * penetration;
}
