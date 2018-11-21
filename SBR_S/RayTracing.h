#pragma once
#include"ReadSTLFile.h"
#include"RayInit.h"


class RayTracing
{
public:
	bool isIntersect_N(ReadSTLFile* input, NRay* ray);//普通光线与面元的相交检测
	bool isIntersect_C(ReadSTLFile* input, CRay* ray,float lambda);//中心光线与面元的相交检测，需要更新场强
	void routine_N(ReadSTLFile* input, NRay* ray,int max_reflect);
	void routine_C(ReadSTLFile* input, CRay* ray, int max_reflect,float lambda);
	void tracing(ReadSTLFile* input, RayInit* rays,int max_reflect,float lambda, float theta, float phi);
};
