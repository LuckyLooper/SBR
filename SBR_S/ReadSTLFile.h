#pragma once
#include"Vector3.h"
#include"TriFace.h"

class ReadSTLFile
{
public:
	unsigned long unTriangles;
	TriFace* module;
	char* memwriter;

public:
	ReadSTLFile();
	~ReadSTLFile();

	bool ReadFile(const char *cfilename);
	bool ReadBinary(const char *buffer);
	int cpyint(const char*& p);
	float cpydouble(const char*& p);

private:
	ReadSTLFile(const ReadSTLFile& a)=delete;
	void operator=(const ReadSTLFile& a)=delete;
};