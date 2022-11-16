#include "IForceAppliable.h"
#include "Force.h"

Force::Force::Force() {
    // this should give a boom
}

Force::Force::Force(IForceAppliable * object) {
    this->object = object;
}

Force::Force::~Force() {
    // nothing?
}

bool Force::Force::isEqual(const Force& other) const {
    return *this == other;
}

bool Force::Force::operator==(const Force& other) const {
    return typeid(*this) == typeid(other) && this->isEqual(other);
}

Force::Gravity::Gravity(IForceAppliable * object) {
    this->val = - object->masse() * GRAVITY_CONST;
}

bool Force::Gravity::isEqual(const Force& other) const {
    auto v = dynamic_cast<const Gravity&>(other);
    return Force::isEqual(v) && v.val == val;
}

Force::ParticuleDrag::ParticuleDrag(IForceAppliable* p, float k1, float k2): Force(p) {
    this->k1 = k1;
    this->k2 = k2;
    this->object = p;
}

Force::Spring::Spring(Particule* p1, Particule* p2, float k): Force(p1) {
    this->connectType = 0;
    this->object = p1;
    this->object2 = p2;
    this->k = k;
    this->dist = p2->position - p1->position;
}

Force::Spring::Spring(Particule* p1, RigidBody* rb, Vector3 localPoint2, float k) {
    // connect particle to rigidbody
    this->connectType = 1;
    this->object = p1;
    this->object2 = rb;
    this->k = k;
    this->localPoint2 = localPoint2;
    this->dist = this->object2->position + this->localPoint2 - this->object->position;
}

Force::Spring::Spring(RigidBody* rb, Vector3 localPoint, Particule* p2, float k) {
    this->connectType = 2;
    this->object = rb;
    this->object2 = p2;
    this->k = k;
    this->localPoint = localPoint;
    this->dist = this->object2->position - this->object->position - this->localPoint; 
}

Force::Spring::Spring(RigidBody* rb1, RigidBody* rb2, Vector3 localPoint1, Vector3 localPoint2) {
    this->connectType = 3;
    this->object = rb1;
    this->object2 = rb2;
    this->k = k;
    this->localPoint = localPoint;
    this->localPoint2 = localPoint2;
    this->dist = this->object2->position + this->localPoint2 - this->object->position - this->localPoint; 
}

Vector3 Force::ParticuleDrag::getForce() {
    Vector3 v = this->object->velocity;
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
    // TODO: not finish
    Vector3 newDist;
    float diff;
    newDist = object2->position + localPoint2 - object->position - localPoint;
    diff = newDist.getMagnitude() - dist.getMagnitude();
    if (diff == 0) return Vector3::Zero();
    // std::cout << particule->position.x << " " << particule->position.y << std::endl;
    // std::cout << particule2->position.x << " " << particule2->position.y << std::endl;
    // std::cout << newDist.x << " " << newDist.y << std::endl << std::endl;
    Vector3 dir = Vector3::Normalized(newDist);
    float magnitude = this->k * diff;
    return dir * magnitude;
}
