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
