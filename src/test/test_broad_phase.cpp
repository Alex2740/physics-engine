// this is a test of the rigid body class
// since there is no new interface available for now,
// the output will just be put in stdout.

#include "physics/Rigidbody.h"
#include "physics/Registry.h"
#include "physics/contact/BoundingSphere.h"
#include "physics/contact/BVHNode.h"
#include "physics/PhysicWorld.h"

#include <iostream>
#include <iomanip>

int main() {
    
    PhysicWorld p = PhysicWorld();

    RigidBody* rb1 = new RigidBody(Vector3(0, 0, 0), 1.0, 1.0, 1.0, 100.0, 1.0f, 1.0f);
    RigidBody* rb2 = new RigidBody(Vector3(3.0f, 5.0f, 0), 1.0, 1.0, 1.0, 100.0, 1.0f, 1.0f);
    RigidBody* rb3 = new RigidBody(Vector3(5.0f, 0, 0), 1.0, 1.0, 1.0, 100.0, 1.0f, 1.0f);

    Registry::RigidRegistry* rr1 = new Registry::RigidRegistry(rb1);
    Registry::RigidRegistry* rr2 = new Registry::RigidRegistry(rb2);
    Registry::RigidRegistry* rr3 = new Registry::RigidRegistry(rb3);
    
    
    
    rr2->addForce(new Force::Gravity(rb2));
    
    float dt = 0.01f;
    for (int i = 0; i < 10000;i++)
    {
        rr1->update(dt);
        rr2->update(dt);
        rr3->update(dt);
       
        /*
        printf("%d : ", rb1->getId());
        rb1->position.print();
        printf("%d : ", rb2->getId());
        rb2->position.print();
        printf("%d :", rb3->getId());
        rb3->position.print();
        */


        BVHNode* root = new BVHNode(nullptr, BoundingSphere(rb1->position, 2.0f), rb1);

        root->insert(rb2, BoundingSphere(rb2->position,2.0f));

        root->insert(rb3, BoundingSphere(rb3->position, 2.0f)); 
        // root->print(0);
        // printf("\n\n");


        // On appelle la broad phase avec sur le BVH root, c'est une fonction récursive
        auto list = PhysicWorld::BroadPhase(root);
        for (int i = 0; list[i] != nullptr; i++) {
            std::cout << "body1: " << list[i]->bodies[0]->getId();
            std::cout << "\nbody2: " << list[i]->bodies[1]->getId();
            std::cout << "\n" << std::endl;
        }
        freePotentialContactList(list);

        // system("pause");

        delete root;
    }
    system("pause");
    
}