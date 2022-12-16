#pragma once

#include "physics/contact/CollisionData.h"

#include <string>
#include <iostream>
#include <fstream>

class CollisionInterpretor
{
private:
    // CollisionInterpretor(const CollisionData&);
    // CollisionInterpretor& operator=(const CollisionInterpretor);
    CollisionData* data = nullptr;
    void writeContact(Contact c);
    std::ofstream out;

public:
    CollisionInterpretor(CollisionData* collisionData, std::string filename);
    void dumpAll();
    ~CollisionInterpretor();
};
