#include <Registry.h>

Registry::ParticuleRegistry::ParticuleRegistry() {
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

// ##### RIGIDBODY #######


Registry::RigidRegistry::RigidRegistry() {
}

Registry::RigidRegistry::RigidRegistry(RigidBody* r) {
    this->rigidbody = r;
}

void Registry::RigidRegistry::addForce(Force::Force* f) {
    this->forceRegistry.push_back(f);
}

void Registry::RigidRegistry::addForceLocalPoint(Force::Force* f, Vector3 coord) {
    this->forceRegistry.push_back(f);
    this->forceApplyType[f] = 1;
    this->forceApplyPoint[f] = coord;
}

void Registry::RigidRegistry::addForceWorldPoint(Force::Force* f, Vector3 coord) {
    this->forceRegistry.push_back(f);
    this->forceApplyType[f] = 2;
    this->forceApplyPoint[f] = coord;
}

void Registry::RigidRegistry::update(float dt) {
    this->rigidbody->ClearAccumulator();
    for (auto f: forceRegistry) {
        Vector3 tmpForce = f->getForce();
        Vector3 tmpCoord;
        switch (this->forceApplyType[f])
        {
        case 0:
            rigidbody->addForce(tmpForce);
            break;
        case 1:
            tmpCoord = forceApplyPoint[f];
            rigidbody->AddForceAtBodyPoint(tmpForce, tmpCoord);
            break;
        case 2:
            tmpCoord = forceApplyPoint[f];
            rigidbody->AddForceAtPoint(tmpForce, tmpCoord);
            break;
        default:
            std::invalid_argument("unexpected value found in rigistry, possibly from a wrong way to introduce a force ath the first time");
            break;
        }
    }
    this->rigidbody->integrate(dt);
    this->rigidbody->ClearAccumulator(); // not necessary. but in case
}

void free() {
    // TODO
}
