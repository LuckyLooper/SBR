#include "Ray.h"

Ray::Ray()
{
}

Ray::Ray(Vector3 _ro, Vector3 _rd,unsigned long _i):origin(_ro),direction(_rd),index(_i)
{
}

Ray::Ray(const Ray & r):origin(r.origin),direction(r.direction),index(r.index)
{
}

Ray::~Ray()
{
}

Ray& Ray::operator=(const Ray & r)
{
	if (this == &r)
		return *this;
	origin = r.origin;
	direction = r.direction;
	index = r.index;
	return *this;
}

CRay::CRay()
{
}

CRay::CRay(Vector3 _ro, Vector3 _rd, unsigned long _i,Vector3 _in,Vector3 _Ei, Vector3 _Es,float _dis):
	Ray(_ro,_rd,_i),in_dir(_in),Ei(_Ei),Es(_Es),distance(_dis)
{
}

CRay::CRay(const CRay &r): Ray(r), in_dir(r.in_dir), Ei(r.Ei), Es(r.Es), distance(r.distance)
{
}

CRay::~CRay()
{
}

CRay& CRay::operator=(const CRay & r)
{
	if (this == &r)
		return *this;
	Ray::operator=(r);
	in_dir = r.in_dir;
	Ei = r.Ei;
	Es = r.Es;
	distance = r.distance;
	return *this;
}

NRay::NRay()
{
}

NRay::NRay(Vector3 _ro, Vector3 _rd, unsigned long _i, int _c) :Ray(_ro, _rd, _i), count(_c)
{
}

NRay::NRay(const NRay & r):Ray(r),count(r.count)
{
}

NRay::~NRay()
{
}

NRay & NRay::operator=(const NRay & r)
{
	if (this == &r)
		return *this;
	Ray::operator=(r);
	count = r.count;
	return *this;
}
