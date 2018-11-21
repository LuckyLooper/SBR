#pragma once

#include<iostream>
#include"Vector3.h"
#include"Complexf.h"


class Ray
{
public:
	Vector3 origin;//出射点位置
	Vector3 direction;//出射点方向
	unsigned long index;//射线出射所在面元ID

public:
	Ray();
	Ray(Vector3 _ro, Vector3 _rd,unsigned long _i);
	Ray(const Ray &r);
	~Ray();
	Ray& operator=(const Ray &r);

};

//射线管的周围四根射线所用类型，只用于射线管分裂判断，不需要电场
class NRay :public Ray
{
public:
	int count;//相交次数，用于射线管分裂判断
public:
	NRay();
	NRay(Vector3 _ro, Vector3 _rd, unsigned long _i, int _c);
	NRay(const NRay &r);
	~NRay();
	NRay& operator=(const NRay &r);
};

//射线管的中心射线所用类型，需要电场用于场强追踪
class CRay:public Ray
{
public:
	Vector3 in_dir;//入射方向
	Vector3 Ei;//入射电场
	Vector3 Es;//出射电场
	float distance;//射线走的总路程

public:
	CRay();
	CRay(Vector3 _ro, Vector3 _rd, unsigned long _i, Vector3 _in, Vector3 _Ei, Vector3 _Es, float _dis);
	CRay(const CRay& r);
	~CRay();
	CRay& operator=(const CRay& r);
};