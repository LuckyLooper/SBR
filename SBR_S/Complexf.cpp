#include "Complexf.h"
#include<iostream>
#define uZero 1e-6

Complexf::Complexf()
{
}

Complexf::Complexf(float _real, float _imag):real(_real),imag(_imag)
{
}

Complexf::Complexf(const Complexf & a):real(a.real),imag(a.imag)
{
}

Complexf::Complexf(float _real):real(_real),imag(0.0)
{
}

Complexf& Complexf::operator=(const Complexf& c)
{
	if (this == &c)
		return *this;
	real = c.real;
	imag = c.imag;
	return *this;
}

Complexf::~Complexf()
{
}

Complexf Complexf::operator+(const Complexf & a) const
{
	return Complexf(real+a.real,imag+a.imag);
}

Complexf & Complexf::operator+=(const Complexf & a)
{
	this->real += a.real;
	this->imag += a.imag;
	return *this;
}

Complexf Complexf::operator-(const Complexf & a) const
{
	return Complexf(real-a.real,imag-a.imag);
}

Complexf & Complexf::operator-=(const Complexf & a)
{
	this->real -= a.real;
	this->imag -= a.imag;
	return *this;
}

Complexf Complexf::operator*(const Complexf & a) const
{
	return Complexf(real*a.real-imag*a.imag,real*a.imag+imag*a.real);
}

Complexf & Complexf::operator*=(const Complexf & a)
{
	real = real*a.real - imag*a.imag;
	imag = real*a.imag + imag*a.real;
	return *this;
}

Complexf Complexf::operator/(const Complexf & a) const
{
	if (fabsf(a.real) <= uZero && fabsf(a.imag) <= uZero)
	{
		std::cerr << "复数除0异常!\n";
		return *this;
	}
	return Complexf((real*a.real+imag*a.imag)/(a.real*a.real+a.imag*a.imag),
		(imag*a.real-real*a.imag)/(a.real*a.real+a.imag*a.imag));
}

Complexf & Complexf::operator/=(const Complexf & a)
{
	if (fabsf(a.real) <= uZero && fabsf(a.imag) <= uZero)
	{
		std::cerr << "复数除0异常!\n";
		return *this;
	}
	real = (real*a.real + imag*a.imag) / (a.real*a.real + a.imag*a.imag);
	imag = (imag*a.real - real*a.imag) / (a.real*a.real + a.imag*a.imag);
	return *this;
}

Complexf Complexf::operator+(float & a) const
{
	return Complexf(real+a,imag);
}

Complexf & Complexf::operator+=(float & a)
{
	real = real + a;
	return *this;
}

Complexf Complexf::operator-(float & a) const
{
	return Complexf(real-a,imag);
}

Complexf & Complexf::operator-=(float & a)
{
	real -= a;
	return *this;
}

Complexf Complexf::operator*(float & a) const
{
	return Complexf(a*real,a*imag);
}

Complexf & Complexf::operator*=(float & a)
{
	real *= a;
	imag *= a;
	return *this;
}

Complexf Complexf::operator/(float & a) const
{
	if (fabsf(a) < uZero)
	{
		std::cerr << "复数除0异常!\n";
		return *this;
	}
	return Complexf(real/a,imag/a);
}

Complexf & Complexf::operator/=(float & a)
{
	if (fabsf(a) < uZero)
	{
		std::cerr << "复数除0异常!\n";
		return *this;
	}
	real /= a;
	imag /= a;
	return *this;
}

void Complexf::print()
{
	std::cout << real << "+" << imag << "i";
}

Complexf exp(const Complexf & a)
{
	float rho = std::exp(a.real);
	float theta = a.imag;
	return Complexf(rho * cos(theta), rho * sin(theta));
}

float abs(const Complexf & a)
{
	return sqrt(a.real*a.real + a.imag*a.imag);
}
