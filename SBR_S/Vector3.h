#pragma once

class Vector3
{
public:
	float x, y, z;

public:
	Vector3();
	Vector3(float x1, float y1, float z1);
	Vector3(const Vector3 &v);
	~Vector3();
	Vector3& operator=(const Vector3 &v);
	Vector3 operator+(const Vector3 &v);
	Vector3& operator+=(const Vector3 &v);
	Vector3 operator-(const Vector3 &v);
	Vector3& operator-=(const Vector3 &v);
	Vector3 operator*(float f);
	friend Vector3 operator* (float f, Vector3& v)
	{
		return Vector3(f * v.x, f * v.y, f * v.z);
	}
	Vector3& operator*=(float f);
	Vector3 operator/(float f);
	Vector3& operator/=(float f);
	Vector3 operator^ (Vector3& v)     //向量叉乘重载
	{
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	Vector3 cross_product(Vector3& v)
	{
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	float operator*(const Vector3 &v)
	{
		return float(x*v.x + y * v.y + z * v.z);
	}
	float dot_product(const Vector3 &v)
	{
		return float(x*v.x + y*v.y + z*v.z);
	}
	Vector3 operator- ()          //向量负号运算符重载
	{
		return Vector3(-x, -y, -z);
	}
	float length();
	Vector3 normalize();
	void print();
};