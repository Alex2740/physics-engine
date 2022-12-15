#include "Vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

float Vector3::getMagnitude()
{
	return sqrtf(Vector3::Dot(*this, *this));
}

Vector3 Vector3::operator=(const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Vector3 Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator+(const Vector3& other)
{
	Vector3 result;
	result = *this;
	result += other;
	return result;
}

Vector3 Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	Vector3 result = Vector3::Zero(); 
	
	result = *this;
	result -= other;
	return result;
}

Vector3 Vector3::operator*(const float other) const
{
	float newX = x * other;
	float newY = y * other;
	float newZ = z * other;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator/(const float other) const
{
	float newX = x / other;
	float newY = y / other;
	float newZ = z / other;
	return Vector3(newX, newY, newZ);
}

bool Vector3::operator==(const Vector3& other) const
{
	return (x == other.x) && (y == other.y) && (z == other.z);
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

float Vector3::Dot(const Vector3 a, const Vector3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::Cross(const Vector3 a, const Vector3 b)
{
	float newX = a.y * b.z - a.z * b.y;
	float newY = a.z * b.x - a.x * b.z;
	float newZ = a.x * b.y - a.y * b.x;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::Normalized(const Vector3 a)
{
	Vector3 v = a;
	if (v.getMagnitude() == 0) {
		return Vector3::Zero();
	}
	return v / v.getMagnitude();
}

float Vector3::Distance(const Vector3 a, Vector3 b)
{
	Vector3 x = a;
	Vector3 y = b;
	return (x - y).getMagnitude();
}

Vector3 Vector3::Project(const Vector3 vector, const Vector3 onNormal)
{
	Vector3 normal = onNormal;
	Vector3 zero = Vector3::Zero();
	if (onNormal == zero)
	{
		return Vector3::Zero();
	}
	float coef = Dot(vector, normal) / (normal.getMagnitude() * normal.getMagnitude());
	return normal * coef;
}

Vector3 Vector3::Zero()
{
	return Vector3(0, 0, 0);
}



void Vector3::print()
{
	std::cout << "Vector3(" << x << "f, " << y << "f, " << z << "f)" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << "Vector3(" << vector.x << ", " << vector.y << ", " << vector.z << ')';
	return os;
}
