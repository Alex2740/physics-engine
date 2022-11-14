#include "Particule.h"

Particule::Particule()
{

}

Particule::Particule(Vector3 _position, float _masse)
{
	inverseMasse = 1 / _masse;
	position = _position;
}

Particule::Particule(Vector3 _position, float _masse, float _damping)
{
	inverseMasse = 1 / _masse;
	damping = _damping;
	position = _position;
}

Particule Particule::operator=(const Particule& other)
{
	this->inverseMasse = other.inverseMasse;
	this->damping = other.damping;
	this->position = other.position;
	this->velocity = other.velocity;
	this->acceleration = other.acceleration;

	return *this;
}

bool Particule::operator==(const Particule& other)
{
	return (inverseMasse == other.inverseMasse)
		&& (damping == other.damping)
		&& (position == other.position)
		&& (velocity == other.velocity)
		&& (acceleration == other.acceleration);
		// && (forces == other.forces);
}

bool Particule::operator!=(const Particule& other)
{
	return !(*this == other);
}

void Particule::setMasse(float _masse)
{
	inverseMasse = 1 / _masse;
}

void Particule::setInverseMasse(float _inverseMasse)
{
	inverseMasse = _inverseMasse;
}

float Particule::masse()
{
	return 1 / inverseMasse;
}


void Particule::integrate(Vector3 forces, float dt)
{

	position += velocity * dt + acceleration * 0.5 * dt * dt;
	acceleration = forces * inverseMasse;
	velocity = velocity * powf(damping, dt);
	velocity += acceleration * dt;
	
}
