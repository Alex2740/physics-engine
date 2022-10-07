#include "Force.h"

Force::Force::Force() {
    // this should give a boom
}

Force::Force::Force(Particule * p) {
    this->particule = p;
}

Force::Gravity::Gravity(Particule * p) {
    this->val = - p->masse() * GRAVITY_CONST;
}

Vector3 Force::Gravity::getForce() {
    return Vector3(0, this->val, 0);
}

Registry::ParticuleRegistry::ParticuleRegistry(Particule* p) {
    this->particule = p;
}

std::vector<Force::Force> Registry::ParticuleRegistry::getRegist() {
    return this->forceRegistry;
}

void Registry::ParticuleRegistry::addForce(Force::Force f) {
    this->forceRegistry.push_back(f);
}

bool Registry::ParticuleRegistry::delForce(Force::Force f) {
    std::remove(this->forceRegistry.begin(), this->forceRegistry.end(), f);
}

void Registry::ParticuleRegistry::update(float dt) {
    Vector3 sum = Vector3::Zero();
    for (auto f: this->forceRegistry) {
        sum += f.getForce();
    }
    this->particule->integrate(sum, dt);
}

bool Registry::ParticuleRegistries::addParticule(Particule* p) {
    if (this->registries.count(p) == 0) return false;
    // TODO: not sure if this works
    // probably not
    this->registries.emplace(p, p);
    return true;
}

bool Registry::ParticuleRegistries::addForce(Particule* p, Force::Force f) {
    if (this->registries.count(p) == 0) return false;
    this->registries[p].addForce(f);
    return true;
}

void Registry::ParticuleRegistries::addForceAll(Force::Force f) {
    for (auto p: this->registries) {
        addForce(p.first, f);
    }
}
