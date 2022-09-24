#pragma once

#include "Vector3.h"
#include "Particule.h"

namespace Forces {
    const float GRAVITATION_CONST = 0.00001f;
    Vector3* gravitation(Particule* p1, Particule* p2);
}

