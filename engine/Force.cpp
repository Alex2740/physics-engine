#include "Force.h"

Force::Force::Force() {
    // this should give a boom
}

Force::Force::Force(Particule * p) {
    this->particule = p;
}

Force::Force::~Force() {
    // nothing?
}

bool Force::Force::isEqual(const Force& obj) const {
    return this->particule == obj.particule;
}

bool Force::Force::operator==(const Force& other) {
    return typeid(this) == typeid(other) && this->isEqual(other);
}

Force::Gravity::Gravity(Particule * p) {
    this->val = - p->masse() * GRAVITY_CONST;
}

bool Force::Gravity::isEqual(const Force& obj) const {
    auto v = dynamic_cast<const Gravity&>(obj);
    return Force::isEqual(v) && v.val == val;
}

Vector3 Force::Gravity::getForce() {
    return Vector3(0, this->val, 0);
}

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
