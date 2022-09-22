#include "Particule.h"

Particule::Particule()
{
	position = new Vector3(0, 0, 0);
	velocity = new Vector3(0, 0, 0);
	acceleration = new Vector3(0, 0, 0);
}

Particule::Particule(Vector3* _position, float _masse)
{
	inverseMasse_ = 1 / _masse;
	position = _position;
	velocity = new Vector3(0, 0, 0);
	acceleration = new Vector3(0, 0, 0);
}

Particule::Particule(Vector3* _position, float _masse, float _damping)
{
	inverseMasse_ = 1 / _masse;
	damping_ = _damping;
	*position = *_position;
	velocity = new Vector3(0, 0, 0);
	acceleration = new Vector3(0, 0, 0);
}

void Particule::setMasse(float _masse)
{
	inverseMasse_ = 1 / _masse;
}

void Particule::setInverseMasse(float _inverseMasse)
{
	inverseMasse_ = _inverseMasse;
}

float Particule::masse()
{
	return 1 / inverseMasse;
}


void Particule::integrate(Vector3* forces, float dt)
{

	*position += *velocity * dt + *acceleration * 0.5 * dt * dt;
	*acceleration = *forces * inverseMasse;
	*velocity = *velocity * powf(damping, dt);
	*velocity += *acceleration * dt;
	
}
