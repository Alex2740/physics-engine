// ######### REGISTRY #########
#pragma once
#include <iostream>

#include "Rigidbody.h"
#include "Particule.h"
#include "Force.h"
#include "Vector3.h"

namespace Registry
{
    class ParticuleRegistry
    {
        // registry for a single particle
        // containing a list of Force
        private:
        Particule* particule;
        std::vector<Force::Force*> forceRegistry;
        // reserved place for future registries

        public:
        ParticuleRegistry();
        ParticuleRegistry(Particule* p);
        ~ParticuleRegistry();
       
        void addForce(Force::Force* f);
        bool delForce(Force::Force* f);

        Vector3 getGravityForce();

        std::vector<Force::Force*> getRegist();

        void update(float dt);
        void free();  // a explicit free function,
                      // since the ~Particule() methods
                      // might be called otherwhere
                      // when the object's copies
                      // are destroyed, which is not
                      // always the end of execution
    };

    class RigidRegistry
    {
        private:
        RigidBody* rigidbody;
        std::vector<Force::Force*> forceRegistry;
        std::map<Force::Force*, int> forceApplyType;
        // 0 for no special point
        // 1 for local point
        // 2 for world point
        std::map<Force::Force*, Vector3> forceApplyPoint;

        public:
        RigidRegistry();
        RigidRegistry(RigidBody* rb);
        ~RigidRegistry();

        void addForce(Force::Force* f);
        void delForce(Force::Force* f);

        void addForceLocalPoint(Force::Force* f, Vector3 coord);
        void addForceWorldPoint(Force::Force* f, Vector3 coord);

        void update(float dt);
        void free();
    };
}

