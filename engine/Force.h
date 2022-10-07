// the new Force class, this will replace the ancient one

#pragma once

#include "Vector3.h"
#include "Particule.h"

namespace Force
{
    const float GRAVITY_CONST = 9.81f;

    class Force
    {
        // the general force class
    protected:
        Particule* particule;
    public:
        Force();
        Force(Particule *p); // the call with particle is expected
        ~Force();
        virtual Vector3 getForce();
    };

    class Gravity: Force
    {
        // the gravity, as a example of Force implementation
    private:
        float val;
    public:
        Gravity(Particule *p);
        Vector3 getForce() override;
    };
}
