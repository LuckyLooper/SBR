#pragma once
#include"ReadSTLFile.h"
#include"RayInit.h"


class RayTracing
{
public:
	bool isIntersect_N(ReadSTLFile* input, NRay* ray);//��ͨ��������Ԫ���ཻ���
	bool isIntersect_C(ReadSTLFile* input, CRay* ray,float lambda);//���Ĺ�������Ԫ���ཻ��⣬��Ҫ���³�ǿ
	void routine_N(ReadSTLFile* input, NRay* ray,int max_reflect);
	void routine_C(ReadSTLFile* input, CRay* ray, int max_reflect,float lambda);
	void tracing(ReadSTLFile* input, RayInit* rays,int max_reflect,float lambda, float theta, float phi);
};
