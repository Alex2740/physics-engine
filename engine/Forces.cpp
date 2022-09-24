#include <cmath>
#include <ostream>
#include <fstream>
#include "Forces.h"

Vector3* Forces::gravitation(Particule* src, Particule* dst) {
    if (src == dst) return nullptr;

    float dist_x = src->position->x - dst->position->x;
    float dist_y = src->position->y - dst->position->y;
    float dist_z = src->position->z - dst->position->z;

    float dist = sqrtf(powf(dist_x, 2) + powf(dist_y, 2) + powf(dist_z, 2));

    if (dist < 0.01) dist = 0.01f;

    float uni_x = dist_x / dist;
    float uni_y = dist_y / dist;
    float uni_z = dist_z / dist;


    float magnitude = Forces::GRAVITATION_CONST * src->masse() * dst->masse() / powf(dist, 2);

    // std::filebuf fb;
    // fb.open("../../log.txt", std::ios_base::app);
    // std::ostream os(&fb);
    // os << src->velocity->magnitude << " " << src->acceleration->magnitude << std::endl;
    // fb.close();

    return new Vector3(magnitude * uni_x, magnitude * uni_y, magnitude * uni_z);
}
