#include "CollisionInterpretor.h"

// CollisionInterpretor::CollisionInterpretor(CollisionData* collisionData, std::string filename)
// {
//     data = collisionData;
//     std::ofstream filestream;
//     filestream.open(filename.c_str() , std::ios::out|std::ios::trunc);
//     std::cout.rdbuf
// }

CollisionInterpretor::CollisionInterpretor(CollisionData* collisionData)
{
    data = collisionData;
}

CollisionInterpretor::~CollisionInterpretor() {}

void CollisionInterpretor::writeContact(Contact c) {
    static int count = 0;
    std::cout << "contact #" << count++ << std::endl;
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
    case 8:
        contactType = "box and plane";
        break;
    
    default:
        contactType = "undefined";
        break;
    }
    std::cout << "\tcontact type: " << contactType << std::endl;
    if (c.contactPoint == Vector3::Zero()) {
        std::cout << "\tcontact point: undefined" << std::endl;
    }
    else {
        std::cout << "\tcontact point: " << c.contactPoint << std::endl;
    }
    if (c.contactNormal == Vector3::Zero()) {
        std::cout << "\tcontact normal: undefined" << std::endl;
    }
    else {
        std::cout << "\tcontact normal: " << c.contactNormal << std::endl;
    }
    std::cout << "\tpenetration: " << c.penetration << std::endl;
}

void CollisionInterpretor::dumpAll(std::string filename) {
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::ofstream out(filename);
    std::cout.rdbuf(out.rdbuf());
    dumpAll();
    std::cout.rdbuf(coutbuf);
}

void CollisionInterpretor::dumpAll() {
    for (auto contact: data->getContactList()) {
        writeContact(contact);
    }
}
