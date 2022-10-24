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

Force::ParticuleDrag::ParticuleDrag(Particule* p, float k1, float k2): Force(p) {
    this->k1 = k1;
    this->k2 = k2;
    this->particule = p;
}

Force::Spring::Spring(Particule* p1, Particule* p2, float k): Force(p1) {
    this->particule = p1;
    this->particule2 = p2;
    this->k = k;
    this->dist = p2->position - p1->position;
}

Vector3 Force::ParticuleDrag::getForce() {
    Vector3 v = this->particule->velocity;
    float magnitude = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    if (magnitude == 0) {
        return Vector3::Zero();
    }
    Vector3 vNormalise = Vector3(v.x / magnitude,v.y/magnitude,v.z/magnitude);
    Vector3 ret = vNormalise * (k1 * v.getMagnitude() + k2 * v.getMagnitude() * v.getMagnitude());
    // printf("%f %f %f\n", vNormalise.x, vNormalise.y, vNormalise.z);
    return ret;
}

Vector3 Force::Gravity::getForce() {
    return Vector3(0, this->val, 0);
}

Vector3 Force::Spring::getForce() {
    Vector3 newDist;
    Vector3 diff;
    newDist = particule2->position - particule->position;
    diff = newDist - dist;
    if (diff == Vector3::Zero()) return Vector3::Zero();
    // std::cout << particule->position.x << " " << particule->position.y << std::endl;
    // std::cout << particule2->position.x << " " << particule2->position.y << std::endl;
    // std::cout << newDist.x << " " << newDist.y << std::endl << std::endl;
    Vector3 dir = Vector3::Normalized(diff);
    float magnitude = this->k * diff.getMagnitude();
    return dir * magnitude;
}
