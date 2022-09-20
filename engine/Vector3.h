#pragma once

#include <math.h>
#include <iostream>

class Vector3
{
private:
    float x_ = 0;
    float y_ = 0;
    float z_ = 0;
    float magnitude_ = 0;

    void setMagnitude();

public:
    const float& x = x_;
    const float& y = y_;
    const float& z = z_;
    const float& magnitude = magnitude_;

    Vector3();
    Vector3(float _x, float _y, float _z);

    void setX(float _x);
    void setY(float _y);
    void setZ(float _z);

    Vector3& operator=(const Vector3& other);
    Vector3& operator+=(const Vector3& other);
    Vector3 operator+(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3 operator-(const Vector3& other);
    Vector3 operator*(const float& other);
    Vector3 operator/(const float& other);
    bool operator==(const Vector3& other);
    bool operator!=(const Vector3& other);

    static float Dot(const Vector3 a, const Vector3 b);
    static Vector3 Cross(const Vector3 a, const Vector3 b);
    static Vector3 Normalized(const Vector3 a);
    static float Distance(const Vector3 a, const Vector3 b);

    static Vector3 Zero();

    void print();
};