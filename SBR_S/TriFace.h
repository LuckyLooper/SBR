#pragma once
#include"Vector3.h"
//三角面源类
class TriFace
{
public:
	Vector3 v0;
	Vector3 v1;
	Vector3 v2;
	Vector3 normal;
	unsigned long index;

public:
	TriFace();
	TriFace(Vector3 _v0, Vector3 _v1, Vector3 _v2,Vector3 _normal);
	~TriFace();
	TriFace& operator=(const TriFace& tf);
	void print();	
};