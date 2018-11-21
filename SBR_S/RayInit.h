#pragma once

#include"Ray.h"
#include"TriFace.h"
#include"Complexf.h"
#include"ReadSTLFile.h"

class RayInit
{
public:
	NRay** NRays;
	CRay** CRays;
	unsigned long rows;
	unsigned long columns;

public:
	RayInit();
	~RayInit();

public:
	bool init(ReadSTLFile* input, float distance, float alpha,float theta, float phi, float lambda);

public:
	RayInit(const RayInit& ri) = delete;
	void operator=(const RayInit& ri) = delete;
};