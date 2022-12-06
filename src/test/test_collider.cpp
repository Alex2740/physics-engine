#include "physics/contact/CollisionDetector.h"
#include "physics/contact/primitive/Box.h"
#include "physics/contact/primitive/Plane.h"
#include "core/Vector3.h"

int main() {
    // Box b = Box();
    // b.halfSize = Vector3(1, 1, 1);
    // b.body = new RigidBody(Vector3::Zero(), 1, 1, 1, 1.0, 1, 1);
    // auto vertices = b.getLocalCoordVertices();
    // for (auto v: vertices) {
    //     std::cout << v << std::endl;
    // }

    // delete b.body;

    Plane p = Plane();
    p.normal = Vector3(1, 0, 0);
    p.offset = 0;

    Vector3 pointExclude = Vector3(1, 0, 0);
    Vector3 pointInclude = Vector3(-1, 0, 1);

    std::cout << "exlude point: " << (p.isIncludePoint(pointExclude)?"include":"exclude") << std::endl;

    std::cout << "include point: " << (p.isIncludePoint(pointInclude)?"include":"exclude") << std::endl;
}
