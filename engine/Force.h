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
// ######### REGISTRY #########
namespace Registry
{
    class ParticuleRegistry
    {
        // registry for a single particle
        // containing a list of Force
        private:
        Particule* particule;
        std::vector<Force::Force> forceRegistry;
        // reserved place for future registries

        public:
        ParticuleRegistry(Particule* p);
        ~ParticuleRegistry();
        void addForce(Force::Force f);
        bool delForce(Force::Force f);

        std::vector<Force::Force> getRegist(void);

        void update(float dt);
    };

    class ParticuleRegistries
    {
        private:
        std::map<Particule*, ParticuleRegistry> registries;

        public:
        // add a new item in the registres
        bool addParticule(Particule* p);
        bool delParticule(Particule* p);

        bool addForce(Particule* p, Force::Force f);
        void addForceAll(Force::Force f);

        void updateAll(float dt); // update all the particles
    };
}

