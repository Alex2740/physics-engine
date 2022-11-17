#include "Quaternion.h"

Quaternion::Quaternion()
{
    w = 1;
    x = 0;
    y = 0;
    z = 0;
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
    w = _w;
    x = _x;
    y = _y;
    z = _z;
}

Quaternion::Quaternion(float _w, Vector3 v)
{
    w = _w;
    x = v.x;
    y = v.y;
    z = v.z;
}

Quaternion::Quaternion(Vector3 euler)
// (roll, putch, yaw)
// code from https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
{
    float cr = cosf(euler.x * 0.5f);
    float sr = sinf(euler.x * 0.5f);
    float cp = cosf(euler.y * 0.5f);
    float sp = sinf(euler.y * 0.5f);
    float cy = cosf(euler.z * 0.5f);
    float sy = sinf(euler.z * 0.5f);

    w = cr * cp * cy + sr * sp * sy;
    x = sr * cp * cy - cr * sp * sy;
    y = cr * sp * cy + sr * cp * sy;
    z = cr * cp * sy - sr * sp * cy;
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
    return Quaternion(w + other.w,
                      x + other.x,
                      y + other.y,
                      z + other.z);
}

Quaternion& Quaternion::operator*=(const Quaternion& other) {
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

Quaternion Quaternion::operator*(const float other)
{
    return Quaternion(w * other, x * other, y * other, z * other);
}

Quaternion Quaternion::operator/(const float divider) {
    return Quaternion(w / divider, x / divider, y / divider, z / divider);
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

bool Quaternion::isUniform(Quaternion q) {
    // test the quaternion is roughly uniform
    return (std::abs(q.getMagnitude() - 1) < 4 * std::numeric_limits<float>::epsilon());
}

Quaternion Quaternion::normalize(Quaternion q) {
    float m = q.getMagnitude();
    return Quaternion(q.w/m, q.x/m, q.y/m, q.z/m);
}

Quaternion Quaternion::conjugation(Quaternion q) {
    return Quaternion(q.w, -q.x, -q.y, -q.z);
}

float Quaternion::dot(Quaternion p, Quaternion q) {
    return (p.w * q.w
          + p.x * q.x
          + p.y * q.y
          + p.z * q.z);
}

Quaternion Quaternion::inverse(Quaternion q) {
    return Quaternion::conjugation(q) / Quaternion::dot(q, q);
}

Quaternion Quaternion::rotateByVector(Vector3 v) {
    this->rotateByQuaternion(Quaternion(0, v));
    return *this;
}

Quaternion Quaternion::rotateByQuaternion(Quaternion q) {
    if (!(Quaternion::isUniform(q))) throw std::invalid_argument("the quaternion input doesn't seem to be valid with a magnitude of 1");

    Quaternion qInv = Quaternion::inverse(q);

    *this = q * (*this) * qInv;
    // auto v = this->getMagnitude();
    return *this;
}

Vector3 Quaternion::toEuler() {
    // code from https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    Vector3 angles;

    // roll (x-axis rotation)
    float sinr_cosp = 2 * (w * x + y * z);
    float cosr_cosp = 1 - 2 * (x * x + y * y);
    angles.x = std::atan2f(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    float sinp = 2 * (w * y - z * x);
    if (std::abs(sinp) >= 1)
        angles.y = std::copysignf(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        angles.y = std::asinf(sinp);

    // yaw (z-axis rotation)
    float siny_cosp = 2 * (w * z + x * y);
    float cosy_cosp = 1 - 2 * (y * y + z * z);
    angles.z = std::atan2f(siny_cosp, cosy_cosp);

    return angles;
}

Quaternion Quaternion::Zero() {
    return Quaternion(0., 0., 0, 0);
}

std::string Quaternion::getString() {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "[ " << w;
    oss << " (" << x;
    oss << " " << y;
    oss << " " << z;
    oss << ")]";
    // std::cout << oss.str() << std::endl;
    return oss.str();
}
