#pragma once
//复数类
class Complexf {
public:
	float real;//实部分量
	float imag;//虚部分量

public:
	//构造函数及赋值运算符重载
	Complexf();
	Complexf(float _real, float _imag);
	Complexf(const Complexf &a);
	Complexf(float _real);
	Complexf& operator=(const Complexf& c);
	~Complexf();
	
	//其他运算符重载
	Complexf operator+(const Complexf &a) const;
	Complexf& operator+=(const Complexf &a);
	Complexf operator-(const Complexf &a)const;
	Complexf& operator-=(const Complexf &a);
	Complexf operator*(const Complexf &a)const;
	Complexf& operator*=(const Complexf &a);
	Complexf operator/(const Complexf &a)const;
	Complexf& operator/=(const Complexf &a);
	Complexf operator+(float &a) const;
	Complexf& operator+=(float &a);
	Complexf operator-(float &a)const;
	Complexf& operator-=(float &a);
	Complexf operator*(float &a)const;
	Complexf& operator*=(float &a);
	Complexf operator/(float &a)const;
	Complexf& operator/=(float &a);
	friend Complexf operator* (float f, Complexf& v)
	{
		return Complexf(f * v.real, f * v.imag);
	}
	Complexf operator-()
	{
		return Complexf(-real, -imag);
	}
	void print();
};
Complexf exp(const Complexf &a);
float abs(const Complexf &a);