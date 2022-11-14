#include "Registry.h"

Registry::ParticuleRegistry::ParticuleRegistry() {
    // this should boom too
}

Registry::ParticuleRegistry::ParticuleRegistry(Particule* p) {
    this->particule = p;
}

Registry::ParticuleRegistry::~ParticuleRegistry() {
    // nothing ?
}

std::vector<Force::Force*> Registry::ParticuleRegistry::getRegist() {
    return this->forceRegistry;
}

void Registry::ParticuleRegistry::addForce(Force::Force* f) {
    this->forceRegistry.push_back(f);
}

bool Registry::ParticuleRegistry::delForce(Force::Force* f) {
    this->forceRegistry.erase(std::remove(this->forceRegistry.begin(), this->forceRegistry.end(), f), this->forceRegistry.end());
    delete f; // have to do this otherwise lost track of it
    return true;
}

Vector3 Registry::ParticuleRegistry::getGravityForce()
{
    for (int i = 0; i < forceRegistry.size(); i++) {
        if (Force::Gravity* gravityForce = dynamic_cast<Force::Gravity*>(forceRegistry.at(i))) {
            return gravityForce->getForce();
        }
    }
    
    return Vector3::Zero();
}

void Registry::ParticuleRegistry::update(float dt) {
    Vector3 sum = Vector3::Zero();
    for (int i = 0; i < this->forceRegistry.size(); i++) {
        sum += forceRegistry.at(i)->getForce();
    }
    this->particule->integrate(sum, dt);
}

void Registry::ParticuleRegistry::free() {
    for (auto p: this->forceRegistry) {
        delete p;
    }
}

bool Registry::ParticuleRegistries::addParticule(Particule* p) {

    this->registries[p] = ParticuleRegistry(p);
    return true;
}

bool Registry::ParticuleRegistries::addForce(Particule* p, Force::Force* f) {
    if (this->registries.count(p) == 0) return false;
    this->registries[p].addForce(f);
    return true;
}

void Registry::ParticuleRegistries::addForceAll(Force::Force* f) {
    for (auto p: this->registries) {
        addForce(p.first, f);
    }
}

void Registry::ParticuleRegistries::updateAll(float dt) {
    for (auto r: this->registries) {
        r.second.update(dt);
        // std::cout << "HERE" << std::endl;
    }
}

Registry::ParticuleRegistries::~ParticuleRegistries() {
    for (auto r: this->registries) {
        r.second.free();
    }
}
