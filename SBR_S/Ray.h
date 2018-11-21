#pragma once

#include<iostream>
#include"Vector3.h"
#include"Complexf.h"


class Ray
{
public:
	Vector3 origin;//�����λ��
	Vector3 direction;//����㷽��
	unsigned long index;//���߳���������ԪID

public:
	Ray();
	Ray(Vector3 _ro, Vector3 _rd,unsigned long _i);
	Ray(const Ray &r);
	~Ray();
	Ray& operator=(const Ray &r);

};

//���߹ܵ���Χ�ĸ������������ͣ�ֻ�������߹ܷ����жϣ�����Ҫ�糡
class NRay :public Ray
{
public:
	int count;//�ཻ�������������߹ܷ����ж�
public:
	NRay();
	NRay(Vector3 _ro, Vector3 _rd, unsigned long _i, int _c);
	NRay(const NRay &r);
	~NRay();
	NRay& operator=(const NRay &r);
};

//���߹ܵ����������������ͣ���Ҫ�糡���ڳ�ǿ׷��
class CRay:public Ray
{
public:
	Vector3 in_dir;//���䷽��
	Vector3 Ei;//����糡
	Vector3 Es;//����糡
	float distance;//�����ߵ���·��

public:
	CRay();
	CRay(Vector3 _ro, Vector3 _rd, unsigned long _i, Vector3 _in, Vector3 _Ei, Vector3 _Es, float _dis);
	CRay(const CRay& r);
	~CRay();
	CRay& operator=(const CRay& r);
};