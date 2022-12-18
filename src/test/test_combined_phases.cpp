// this is a test of the rigid body class
// since there is no new interface available for now,
// the output will just be put in stdout.

#include "physics/Rigidbody.h"
#include "physics/Registry.h"
#include "physics/contact/BoundingSphere.h"
#include "physics/contact/BVHNode.h"
#include "physics/PhysicWorld.h"

#include "physics/contact/CollisionInterpretor.h"
#include "physics/contact/CollisionDetector.h"
#include "physics/contact/CollisionData.h"

#include <iostream>

int main() {
    
    PhysicWorld p = PhysicWorld();

    // RigidBody* rb1 = new RigidBody(Vector3(0, 0, 0), 1.0, 1.0, 1.0, 100.0, 1.0f, 1.0f);
    // RigidBody* rb2 = new RigidBody(Vector3(3.0f, 5.0f, 0), 1.0, 1.0, 1.0, 100.0, 1.0f, 1.0f);
    // RigidBody* rb3 = new RigidBody(Vector3(5.0f, 0, 0), 1.0, 1.0, 1.0, 100.0, 1.0f, 1.0f);

    Box b1 = Box();
    b1.halfSize = Vector3(1, 1, 1);
    b1.body = new RigidBody(Vector3::Zero(), 1, 1, 1, 1.0f, 0.9f, 0.9f);
    b1.body->primitive = &b1;

    Box b2 = Box();
    b2.halfSize = Vector3(1, 1, 1);
    b2.body = new RigidBody(Vector3(2.1, 0, 0), 1, 1, 1, 1.0f, 0.9f, 0.9f);
    b2.body->primitive = &b2;

    Registry::RigidRegistry* rr1 = new Registry::RigidRegistry(b1.body);
    Registry::RigidRegistry* rr2 = new Registry::RigidRegistry(b2.body);

    Registry::RigidRegistry* regists[] = {rr1, rr2};
    
    float dt = 0.01f;
    for (int i = 0; i < 1000;i++)
    {
        for (auto r: regists) {
            r->update(dt);
        }

        BVHNode* root = new BVHNode(nullptr, &b1);
        root->insert(dynamic_cast<Primitive*>(&b2));

        // root->print(0);
        // printf("\n\n");


        // On appelle la broad phase avec sur le BVH root, c'est une fonction récursive
        std::cout << "Broad Phase" << std::endl;
        auto listBroad = PhysicWorld::BroadPhase(root);
        for (int i = 0; listBroad[i] != nullptr; i++) {
            std::cout << "body1: " << listBroad[i]->bodies[0]->getId();
            std::cout << "\nbody2: " << listBroad[i]->bodies[1]->getId();
            std::cout << "\n" << std::endl;
        }

        CollisionData listNarrow = CollisionData();
        CollisionDetector::detectList(listBroad, &listNarrow);
        CollisionInterpretor intp = CollisionInterpretor(&listNarrow);

        intp.dumpAll();

        delete root;
        freePotentialContactList(listBroad);
    }
    system("pause");
}