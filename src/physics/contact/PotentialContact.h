#include "Rigidbody.h"

class PotentialContact {

private :
	// Contient les 2 rigidbody potentiellement en contact (broad phase)
	RigidBody* bodies[2];

public : 
	PotentialContact(RigidBody** bodies);

};