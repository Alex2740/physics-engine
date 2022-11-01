// The class Quaternion define an object Quaternion
// and do the calculation

#pragma once
#pragma comment(lib, "legacy_stdio_definitions.lib")
// add this because microsoft is a fucked up company

#include "Vector3.h"

// #include <stdio.h>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>

# define M_PI 3.14159265358979323846

class Quaternion
{

public:
    float w, x, y, z; // w + x * i + y * j + z * k
    Quaternion(float _w, float _x, float _y, float _z);
    Quaternion(float _w, Vector3 v);
    Quaternion(Vector3 euler);
    ~Quaternion();

    float getMagnitude();

    Quaternion& operator+=(const Quaternion& other);
    Quaternion operator+(const Quaternion& other);
    Quaternion& operator*=(const Quaternion& other);
    Quaternion operator*(const Quaternion& other);
    Quaternion operator/(const float divider);
    bool operator==(const Quaternion& other) const;
    bool operator!=(const Quaternion& other) const;

    // there are multiples functions which are bound with the
    // different "multiply" operation, since we don't need all
    // of them, we only implement what we need.

    static bool isUniform(Quaternion q);
    static Quaternion conjugation(Quaternion q);
    static float dot(Quaternion p, Quaternion q);
    static Quaternion inverse(Quaternion q);

    Quaternion rotateByVector(Vector3 v); // rotate by vector (0, v.x, v.y, v.z)
    Quaternion rotateByQuaternion(Quaternion q);

    Vector3 toEuler();
    
    static Quaternion Zero();

    std::string getString();
};
