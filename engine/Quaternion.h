// The class Quaternion define an object Quaternion
// and do the calculation

#pragma once

class Quaternion
{

public:
    float w, x, y, z; // w + x * i + y * j + z * k
    Quaternion(float _w, float _x, float _y, float _z);
    ~Quaternion();

    float getMagnitude();

    Quaternion& operator+=(const Quaternion& other);
    Quaternion operator+(const Quaternion& other);
    Quaternion operator*=(const Quaternion& other);
    Quaternion operator*(const Quaternion& other);
    bool operator==(const Quaternion& other) const;
    bool operator!=(const Quaternion& other) const;

    static float Dot(const Quaternion a, const Quaternion b);
    // there are multiples functions which are bound with the
    // different "multiply" operation, since we don't need all
    // of them, we only implement what we need.
    
    static Quaternion Zero();
};
