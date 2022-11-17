// this is a test of the rigid body class
// since there is no new interface available for now,
// the output will just be put in stdout.

#include "physics/Rigidbody.h"
#include "physics/Registry.h"

#include <iostream>
#include <iomanip>

int main() {
    RigidBody* rigidBody = new RigidBody(Vector3(0, 0, 0), 1.0, 1.0, 1.0, 100.0, 1.0f, 1.0f);
    Registry::RigidRegistry* rr = new Registry::RigidRegistry(rigidBody);

    Vector3 localPoint = Vector3(100, 0, 0);
    Vector3 localPoint2 = Vector3(0, 0, 0);
    rr->addForceLocalPoint(new Force::FixAngleForce(rigidBody, localPoint, Vector3(0,100,0)), localPoint);
    rr->addForceLocalPoint(new Force::FixAngleForce(rigidBody, localPoint2, Vector3(0, -100, 0)), localPoint2);
    rr->addForce(new Force::Gravity(rigidBody));
    
    float dt = 0.1f;
    for (int i = 0; i < 100000; i++)
    {
        rr->update(dt);
        std::cout << std::setprecision(2);
        std::cout << rigidBody->position.x << " " << rigidBody->position.y << " " << rigidBody->position.z << " ";
        std::cout << rigidBody->getOrientation().toEuler().x << std::endl;
    }
    
}