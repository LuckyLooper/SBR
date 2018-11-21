#include<fstream>
#include "RayInit.h"
#define ACCURACY 5
#define PI 3.141592654
RayInit::RayInit():NRays(NULL),CRays(NULL),rows(0),columns(0)
{
}

RayInit::~RayInit()
{
	unsigned long i = 0;
	for (i = 0; i < rows + 1; ++i)
	{
		delete[] NRays[i];
	}
	delete[] NRays;
	for (i = 0; i < rows; ++i)
	{
		delete[] CRays[i];
	}
	delete[] CRays;
}

float min(float _f1, float _f2)
{
	return _f1 <= _f2 ? _f1 : _f2;
}

float max(float _f1, float _f2)
{
	return _f1 >= _f2 ? _f1 : _f2;
}

bool RayInit::init(ReadSTLFile * input, float distance, float alpha,float theta, float phi, float lambda)
{
	

	//入射电场初始化
	float k0 = 2.0*PI*lambda;
	float Ex = cos(PI + phi)*cos(PI - theta)*cos(alpha) - sin(PI + phi)*sin(alpha);
	float Ey = sin(PI + phi)*cos(PI - theta)*cos(alpha) + cos(PI + phi)*sin(alpha);
	float Ez = -1 * sin(PI - theta)*cos(alpha);
	Vector3 E0 = Vector3(Ex, Ey, Ez);

	//将模型投影到入射平面，求出其范围
	float xr, yr, zr, ytheta, zphi;
	float ytmin, ytmax, zpmin, zpmax;
	TriFace* it = input->module;
	xr = distance;
	ytmin = cos(theta)*cos(phi)*(it[0].v0.x) +
		cos(theta)*sin(phi)*(it[0].v0.y)
		- sin(theta)*(it[0].v0.z);
	zpmin = cos(phi)*(it[0].v0.y) -
		sin(phi)*(it[0].v0.x);
	ytmax = ytmin;
	zpmax = zpmin;
	for (unsigned long i = 1; i < input->unTriangles; ++i)
	{
		ytheta = cos(theta)*cos(phi)*(it[i].v0.x) +
			cos(theta)*sin(phi)*(it[i].v0.y)
			- sin(theta)*(it[i].v0.z);
		zphi = cos(phi)*(it[i].v0.y) -
			sin(phi)*(it[i].v0.x);
		ytmin = min(ytmin, ytheta);
		ytmax = max(ytmax, ytheta);
		zpmin = min(zpmin, zphi);
		zpmax = max(zpmax, zphi);

		ytheta = cos(theta)*cos(phi)*(it[i].v1.x) +
			cos(theta)*sin(phi)*(it[i].v1.y)
			- sin(theta)*(it[i].v1.z);
		zphi = cos(phi)*(it[i].v1.y) -
			sin(phi)*(it[i].v1.x);
		ytmin = min(ytmin, ytheta);
		ytmax = max(ytmax, ytheta);
		zpmin = min(zpmin, zphi);
		zpmax = max(zpmax, zphi);

		ytheta = cos(theta)*cos(phi)*(it[i].v2.x) +
			cos(theta)*sin(phi)*(it[i].v2.y)
			- sin(theta)*(it[i].v2.z);
		zphi = cos(phi)*(it[i].v2.y) -
			sin(phi)*(it[i].v2.x);
		ytmin = min(ytmin, ytheta);
		ytmax = max(ytmax, ytheta);
		zpmin = min(zpmin, zphi);
		zpmax = max(zpmax, zphi);
	}

	//求出投影平面两个方向上的射线数目
	unsigned long M = ACCURACY / lambda*(ytmax - ytmin);
	unsigned long N = ACCURACY / lambda*(zpmax - zpmin);
	rows = M + 1;
	columns = N + 1;

	//生成入射光线
	Vector3 ray_dir = Vector3(-sin(theta)*cos(phi), -sin(theta)*sin(phi), -cos(theta));
	//射线管的周围四根射线
	NRays = new NRay* [rows+1];
	for (unsigned long i = 0; i < rows+1; ++i)
	{
		NRays[i] = new NRay [columns+1];
	}
	for (unsigned long i = 0; i < rows+1; ++i)
	{
		for (unsigned long j = 0; j < columns+1; ++j)
		{
			ytheta = ytmin + lambda / ACCURACY * i;
			zphi = zpmin + lambda / ACCURACY * j;
			xr = sin(theta)*cos(phi)*distance +
				cos(theta)*cos(phi)*ytheta -
				sin(phi)*zphi;
			yr = sin(theta)*sin(phi)*distance +
				cos(theta)*sin(phi)*ytheta +
				cos(phi)*zphi;
			zr = cos(theta)*distance - sin(theta)*ytheta;
			NRays[i][j].origin = Vector3(xr, yr, zr);
			NRays[i][j].direction = ray_dir;
			NRays[i][j].index = 0;
			NRays[i][j].count = 0;
		}
	}
	//射线管的中心射线
	std::ofstream out;
	out.open("LOG/rays.log");
	CRays = new CRay*[rows];
	for (unsigned long i = 0; i < rows; ++i)
	{
		CRays[i] = new CRay[columns];
	}
	for (unsigned long i = 0; i < rows ; ++i)
	{
		for (unsigned long j = 0; j < columns ; ++j)
		{
			CRays[i][j].origin =
				(NRays[i][j].origin + NRays[i + 1][j].origin + NRays[i][j + 1].origin + NRays[i + 1][j + 1].origin) / 4.0;
			CRays[i][j].direction = ray_dir;
			CRays[i][j].index = 0;
			CRays[i][j].in_dir = ray_dir;
			CRays[i][j].Ei = E0;
			CRays[i][j].Es=E0;
			CRays[i][j].distance=0.0;
			out << CRays[i][j].origin.x << " " << CRays[i][j].origin.y << " " << CRays[i][j].origin.z << std::endl;
		}
	}
	out.close();
	return true;
}
