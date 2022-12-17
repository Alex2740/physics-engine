#include "Plane.h"

bool Plane::isIncludePoint(Vector3 point) {
    normal = Vector3::Normalized(normal);
    if (normal == Vector3::Zero()) {
        throw std::runtime_error("invalid normal value zero");
    }
    float distance = Vector3::Dot(point, normal);
    return (distance < offset);
}

float Plane::getDistanceToPoint(Vector3 point) {
    normal = Vector3::Normalized(normal);
    if (normal == Vector3::Zero()) {
        throw std::runtime_error("invalid normal value zero");
    }
    float distance = Vector3::Dot(point, normal);
    return distance - offset;
}

int Plane::getType() {
    return 2;
}