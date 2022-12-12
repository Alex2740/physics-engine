#include "CollisionInterpretor.h"

CollisionInterpretor::CollisionInterpretor(CollisionData* collisionData, std::string filename)
{
    data = collisionData;
    out.open(filename, std::ios::out|std::ios::trunc);
}

CollisionInterpretor::~CollisionInterpretor()
{
    out.close();
}

void CollisionInterpretor::writeContact(Contact c) {
    static int count = 0;
    out << "contact #" << count++ << std::endl;
}

void CollisionInterpretor::dumpAll() {
    for (auto contact: data->getContactList()) {
        writeContact(contact);
    }
}
