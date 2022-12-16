#include "physics/Rigidbody.h"

class PotentialContact {

public :
	// Contient les 2 rigidbody potentiellement en contact (broad phase)
	RigidBody* bodies[2];

	PotentialContact();
};