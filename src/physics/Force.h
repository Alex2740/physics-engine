// the new Force class, this will replace the ancient one

#pragma once

#include <map>

#include "Particule.h"
#include "Rigidbody.h"
#include "Vector3.h"

// ############ FORCE ###########
namespace Force
{
    const float GRAVITY_CONST = 9.81f;

    class Force
    {
        // the general force class
    protected:
        IForceAppliable* object;
        // Particule* particule;
        virtual bool isEqual(const Force& obj) const;
    public:
        Force();
        Force(IForceAppliable* obj);
        // Force(Particule *p); // the call with particle is expected
        // Force(RigidBody* rb);
        ~Force();
        virtual Vector3 getForce() = 0;
        bool operator==(const Force& other) const;
    };

    class Gravity: public Force
    {
        // the gravity, as a example of Force implementation
    private:
        float val;
    protected:
        bool isEqual(const Force& obj) const override;
    public:
        Gravity(IForceAppliable *p);
        Vector3 getForce() override;
    };

    class ParticuleDrag: public Force {
    private:
        float k1=3;
        float k2=4;
    public:
        ParticuleDrag(IForceAppliable* p, float k1, float k2);
        Vector3 getForce() override;
    };

    class Spring: public Force {
    // build a 'static' string between the two particles/rigidbodies,
    // the force will be the one p1 taken from p2;
    private:
        float k;
        Vector3 dist;
        // the following are used in case the second member is a particle
        IForceAppliable* object2;

        // the following var are used for RigidBody
        Vector3 localPoint = Vector3::Zero();
        Vector3 localPoint2 = Vector3::Zero();

        int connectType = 0;
        // 0 for particle-particle
        // 1 for particle-rigidbody
        // 2 for rigidbody-particle
        // 3 for rigidbody-rigidbody
    public:
        // considering all the possibilities:
        // Particle-Particle
        // Particle-RigidBody
        // etc.
        Spring(Particule* p1, Particule* p2, float k);
        Spring(Particule* p1, RigidBody* rb, Vector3 localPoint, float k);
        Spring(RigidBody* rb, Vector3 localPoint, Particule* p2, float k);
        Spring(RigidBody* rb1, RigidBody* rb2, Vector3 localPoint1, Vector3 localPoint2);
        Vector3 getForce() override;
    };
}
