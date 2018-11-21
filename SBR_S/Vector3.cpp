#include"Vector3.h"
#include<iostream>

#define uZero 1e-6

Vector3::Vector3()
{
}

Vector3::Vector3(float x1, float y1, float z1):x(x1),y(y1),z(z1)
{
}

Vector3::Vector3(const Vector3 & v):x(v.x),y(v.y),z(v.z)
{
}

Vector3::~Vector3()
{
}

Vector3& Vector3::operator=(const Vector3 & v)
{
	if (this == &v)
		return *this;
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3 & v)
{
	return Vector3(x+v.x,y+v.y,z+v.z);
}

Vector3 & Vector3::operator+=(const Vector3 & v)
{
	x += v.x; y += v.y; z += v.z; 
	return *this;
}

Vector3 Vector3::operator-(const Vector3 & v)
{
	return Vector3(x-v.x,y-v.y,z-v.z);
}

Vector3 & Vector3::operator-=(const Vector3 & v)
{
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

Vector3 Vector3::operator*(float f)
{
	return Vector3(f*x,f*y,f*z);
}

Vector3 & Vector3::operator*=(float f)
{
	x *= f, y *= f, z *= f;
	return *this;
}

Vector3 Vector3::operator/(float f)
{
	if (fabsf(f) < uZero)
	{
		std::cerr << "³ý0Òì³£!\n";
		return *this;
	}
	return Vector3(x / f, y / f, z / f);
}

Vector3 & Vector3::operator/=(float f)
{
	if (fabsf(f) < uZero)
	{
		std::cerr << "³ý0Òì³£!\n";
		return *this;
	}
	else
	{
		this->x = x / f;
		this->y = y / f;
		this->z = z / f;
		return *this;
	}
}



float Vector3::length()
{
	return sqrt(x*x+y*y+z*z);
}

Vector3 Vector3::normalize()
{
	float len = length();
	if (len < uZero)len = 1;
	return Vector3(x/len,y/len,z/len);
}

void Vector3::print()
{
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}






