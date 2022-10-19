// the new Force class, this will replace the ancient one

#pragma once

#include <map>

#include "Vector3.h"
#include "Particule.h"
// ############ FORCE ###########
namespace Force
{
    const float GRAVITY_CONST = 9.81f;

    class Force
    {
        // the general force class
    protected:
        Particule* particule;
        virtual bool isEqual(const Force& obj) const;
    public:
        Force();
        Force(Particule *p); // the call with particle is expected
        ~Force();
        virtual Vector3 getForce() = 0;
        bool operator==(const Force& other);
    };

    class Gravity: public Force
    {
        // the gravity, as a example of Force implementation
    private:
        float val;
    protected:
        bool isEqual(const Force& obj) const override;
    public:
        Gravity(Particule *p);
        Vector3 getForce() override;
    };

    class ParticuleDrag :public Force {
    private:
        float k1=3;
        float k2=4;
    public:
        ParticuleDrag(Particule* p);
        Vector3 getForce() override;
    };
}
