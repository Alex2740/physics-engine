#include "Particule.h"
#include "Vector3.h"

class ParticleContact {

public:
	Particule* particule[2];

	float restitution;

	float penetration;

	Vector3 contactNormal;

	void resolve(float duration);

	float calculateSeparatingVelocity();


private : 

	void resolveVelocity();

	void resolveInterpenetration();




};