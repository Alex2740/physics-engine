#pragma once

#include "physics/contact/CollisionData.h"
#include <cstring>

class CollisionInterpretor
{
public:
    CollisionInterpretor(CollisionData* collisionData, std::string filename);
    ~CollisionInterpretor();
};
