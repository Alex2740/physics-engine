#pragma once

#include <cmath>
#include <iostream>

class Vector3
{
public:
    float x = 0;
    float y = 0;
    float z = 0;

    Vector3();
    Vector3(float _x, float _y, float _z);

    float getMagnitude();

    Vector3 operator=(const Vector3& other);
    Vector3 operator+=(const Vector3& other);
    Vector3 operator+(const Vector3& other);
    Vector3 operator-=(const Vector3& other);
    Vector3 operator-(const Vector3& other);
    Vector3 operator*(const float& other);
    Vector3 operator/(const float& other);
    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vector);

    static float Dot(const Vector3 a, const Vector3 b);
    static Vector3 Cross(const Vector3 a, const Vector3 b);
    static Vector3 Normalized(const Vector3 a);
    static float Distance(const Vector3 a, const Vector3 b);
    static Vector3 Project(const Vector3 vector, const Vector3 onNormal);

    static Vector3 Zero();

    void print();
};