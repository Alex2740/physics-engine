#include "physics/contact/CollisionInterpretor.h"
#include "physics/contact/CollisionDetector.h"
#include "physics/contact/CollisionData.h"
#include "physics/contact/primitive/Box.h"
#include "physics/contact/primitive/Plane.h"
#include "core/Vector3.h"

int main() {
    // create a box
    Box b = Box();
    b.halfSize = Vector3(1, 1, 1);
    b.body = new RigidBody(Vector3::Zero(), Vector3(1, 1, 1), 1.0, 1, 1);

    // create a sphere, the rigid body is not correct, but doesn't really matter
    Sphere s = Sphere();
    s.radius = 1;
    s.body = new RigidBody(Vector3(-1, -1, -1), Vector3(1, 1, 1), 1.0, 1, 1);
    s.offset = Matrix4(Matrix3::eye(), s.body->position);

    // create a second sphere
    Sphere s2 = Sphere();
    s2.radius = 2;
    s2.body = new RigidBody(Vector3(1, 1, 1), Vector3(1, 1, 1), 2.0, 1, 1);
    s2.offset = Matrix4(Matrix3::eye(), s2.body->position);

    // create a plane
    Plane p = Plane();
    p.normal = Vector3(1, 0, 0);
    p.offset = 0;

    Vector3 pointExclude = Vector3(1, 0, 0);
    Vector3 pointInclude = Vector3(-0.1, 0, 0.1);

    std::cout << "exlude point: " << (p.isIncludePoint(pointExclude)?"include":"exclude") << std::endl;
    std::cout << "include point: " << (p.isIncludePoint(pointInclude)?"include":"exclude") << std::endl;

    CollisionData list = CollisionData();
    CollisionDetector::BoxAndPoint(b, pointInclude, &list);
    CollisionDetector::AnyAndAny(s, s2, &list);
    CollisionDetector::AnyAndAny(s, b, &list);
    CollisionDetector::AnyAndAny(b, s2, &list);
    CollisionDetector::AnyAndAny(s, p, &list);
    CollisionDetector::AnyAndAny(s2, p, &list);

    CollisionInterpretor intp = CollisionInterpretor(&list);
    intp.dumpAll();
}
