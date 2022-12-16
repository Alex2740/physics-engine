#include "Box.h"

std::array<Vector3, 8> Box::getLocalCoordVertices() {
    // return the coord for all vertives in a FIXED order
    std::array<Vector3, 8> ret = std::array<Vector3, 8>();
    // defensive
    if (body == nullptr || halfSize == Vector3::Zero() || body == nullptr) return ret;

    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            for (int k = -1; k <= 1; k += 2) {
                Vector3 relativeDepl = Vector3(
                    i * halfSize.x,
                    j * halfSize.y,
                    k * halfSize.z
                );
                int index = ((i>0)?0:4) + ((j>0)?0:2) + ((k>0)?0:1);
                ret[index] = offset * (body->position + relativeDepl);
            }
        }
    }

    return ret;
}

Vector3 Box::getAxis(int i)
{
    return Vector3(offset.data[i], offset.data[i + 4], offset.data[i + 8]);
}

float Box::projectOnAxis(Vector3 axis)
{
    float projection = 0;
    
    projection += halfSize.x * fabs(Vector3::Dot(getAxis(0), axis));
    projection += halfSize.y * fabs(Vector3::Dot(getAxis(1), axis));
    projection += halfSize.z * fabs(Vector3::Dot(getAxis(2), axis));

    return projection;
}
