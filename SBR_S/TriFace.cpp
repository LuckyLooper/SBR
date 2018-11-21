#include"TriFace.h"
#include<iostream>

TriFace::TriFace()
{
}

TriFace::TriFace(Vector3 _v0, Vector3 _v1, Vector3 _v2, Vector3 _normal):
	v0(_v0),v1(_v1),v2(_v2),normal(_normal)
{
}

TriFace::~TriFace()
{
}

TriFace & TriFace::operator=(const TriFace & tf)
{
	if (this == &tf)
		return *this;
	v0 = tf.v0;
	v1 = tf.v1;
	v2 = tf.v2;
	normal = tf.normal;
	index = tf.index;
	return *this;
}

void TriFace::print()
{
	std::cout << "v0: ";
	this->v0.print();
	std::cout << "v1: ";
	this->v1.print();
	std::cout << "v2: ";
	this->v2.print();
	std::cout << "normal: ";
	this->normal.print();
}


