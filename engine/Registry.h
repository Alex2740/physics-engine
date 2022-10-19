// ######### REGISTRY #########

#include <Particule.h>
#include <Force.h>

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

