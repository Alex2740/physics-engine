#include "Quaternion.h"

#include <cmath>

Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
    w = _w;
    x = _x;
    y = _y;
    z = _z;
}

Quaternion::~Quaternion()
{
}

float Quaternion::getMagnitude() {
    return sqrtf(powf(w, 2) + powf(x, 2) + powf(y, 2) + powf(z, 2));
}

Quaternion& Quaternion::operator+=(const Quaternion& other) {
    this->w += other.w;
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

Quaternion Quaternion::operator+(const Quaternion& other) {
    return Quaternion(x + other.x,
                      y + other.y,
                      z + other.z,
                      w + other.w);
}

Quaternion Quaternion::operator*=(const Quaternion& other) {
    float tmpW, tmpX, tmpY, tmpZ;
    tmpW = w;
    tmpX = x;
    tmpY = y;
    tmpZ = z;

    this->w = tmpW * other.w - tmpX * other.x - tmpY * other.y - tmpZ * other.z;
    this->x = tmpX * other.w + tmpW * other.x + tmpZ * other.y - tmpY * other.z;
    this->y = tmpY * other.w - tmpZ * other.x + tmpW * other.y + tmpX * other.z;
    this->z = tmpW * other.z + tmpY * other.x - tmpX * other.y + tmpW * other.z;

    return *this;
}

Quaternion Quaternion::operator*(const Quaternion& other) {
    float tmpW, tmpX, tmpY, tmpZ;

    tmpW = w * other.w - x * other.x - y * other.y - z * other.z;
    tmpX = x * other.w + w * other.x + z * other.y - y * other.z;
    tmpY = y * other.w - z * other.x + w * other.y + x * other.z;
    tmpZ = w * other.z + y * other.x - x * other.y + w * other.z;

    return Quaternion(tmpW, tmpX, tmpY, tmpZ);
}

bool Quaternion::operator==(const Quaternion& other) const {
    return (this->w == other.w 
        &&  this->x == other.x
        &&  this->y == other.y
        &&  this->z == other.z);
}
bool Quaternion::operator!=(const Quaternion& other) const {
    return (!(*this == other));
}

