#include "CollisionInterpretor.h"

CollisionInterpretor::CollisionInterpretor(CollisionData* collisionData, std::string filename)
{
    data = collisionData;
    out.open(filename.c_str() , std::ios::out|std::ios::trunc);
}

CollisionInterpretor::~CollisionInterpretor()
{
    out.close();
}

void CollisionInterpretor::writeContact(Contact c) {
    static int count = 0;
    out << "contact #" << count++ << std::endl;
    std::string contactType;
    switch (-1)
    {
    case 0:
        contactType = "sphere & sphere";
        break;
    case 1:
        contactType = "sphere and halfspace";
        break;
    case 2:
        contactType = "sphere and plane";
        break;
    case 3:
        contactType = "sphere and point";
        break;
    case 4:
        contactType = "box and half space";
        break;
    case 5:
        contactType = "box and sphere";
        break;
    case 6:
        contactType = "box and box";
        break;
    case 7:
        contactType = "box and point";
        break;
    
    default:
        throw std::runtime_error("undetermined contact type def");
        break;
    }
    out << "contact type: " << contactType << std::endl;
}

void CollisionInterpretor::dumpAll() {
    for (auto contact: data->getContactList()) {
        writeContact(contact);
    }
}
