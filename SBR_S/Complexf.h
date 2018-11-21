#pragma once
//������
class Complexf {
public:
	float real;//ʵ������
	float imag;//�鲿����

public:
	//���캯������ֵ���������
	Complexf();
	Complexf(float _real, float _imag);
	Complexf(const Complexf &a);
	Complexf(float _real);
	Complexf& operator=(const Complexf& c);
	~Complexf();
	
	//�������������
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