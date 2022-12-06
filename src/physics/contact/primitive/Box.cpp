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