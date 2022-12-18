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
    std::streambuf* out;

public:
    CollisionInterpretor(CollisionData* collisionData);

    void dumpAll();
    void dumpAll(std::string filename);
    ~CollisionInterpretor();
};
