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


// ######### REGISTRY #########
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

        std::vector<Force::Force*> getRegist(void);

        void update(float dt);
        void free();  // a explicit free function,
                      // since the ~Particule() methods
                      // might be called otherwhere
                      // when the object's copies
                      // are destroyed, which is not
                      // always the end of execution
    };

    class ParticuleRegistries
    {
        private:
        std::map<Particule*, ParticuleRegistry> registries;

        public:
        // add a new item in the registres
        ~ParticuleRegistries();

        bool addParticule(Particule* p);
        bool delParticule(Particule* p);

        bool addForce(Particule* p, Force::Force* f);
        void addForceAll(Force::Force* f);

        void updateAll(float dt); // update all the particles
    };
}

