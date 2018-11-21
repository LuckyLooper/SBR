#include "ReadSTLFile.h"
#include"Vector3.h"
#include"TriFace.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>

ReadSTLFile::ReadSTLFile()
{
	unTriangles = 0;
	module = NULL;
	memwriter = NULL;
}

ReadSTLFile::~ReadSTLFile()
{
	if (module != NULL)
		delete[] module;
	module = NULL;
}

bool ReadSTLFile::ReadFile(const char * cfilename)
{
	FILE * pFile;
	long lSize;
	char* buffer;
	size_t result;
	TriFace* ret=NULL;

	/* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开 */
	fopen_s(&pFile, cfilename, "rb");
	if (pFile == NULL)
	{
		fputs("File error", stderr);
		exit(1);
	}

	/* 获取文件大小 */
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	/* 分配内存存储整个文件 */
	buffer = (char*)malloc(sizeof(char)*lSize);
	if (buffer == NULL)
	{
		fputs("Memory error", stderr);
		exit(2);
	}

	/* 将文件拷贝到buffer中 */
	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize)
	{
		fputs("Reading error", stderr);
		exit(3);
	}


	/* 结束演示，关闭文件并释放内存 */
	fclose(pFile);

	std::ios::sync_with_stdio(false);
	if (buffer[79] != '\0')//判断格式
	{
		std::cerr << "请使用二进制STL文件" << std::endl;
		exit(1);
	}
	else
	{
		ReadBinary(buffer);
	}
	std::ios::sync_with_stdio(true);

	free(buffer);
	return true;
}


  bool ReadSTLFile::ReadBinary(const char * buffer)
 {
	 printf("loading STL files...\n");

	 const char* p = buffer;
	 char name[80];
	 unsigned long i;
	 float tmpx, tmpy, tmpz;
	 memcpy(name, p, 80);
	 p += 80;
	 unTriangles = cpyint(p);
	 TriFace* res = new TriFace[unTriangles];
	 TriFace tmp_tri;
	 for (i = 0; i < unTriangles; i++)
	 {
		 tmpx = cpydouble(p);
		 tmpy = cpydouble(p);
		 tmpz = cpydouble(p);
		 tmp_tri.normal = Vector3(tmpx, tmpy, tmpz);
		 tmpx = cpydouble(p);
		 tmpy = cpydouble(p);
		 tmpz = cpydouble(p);
		 tmp_tri.v0 = Vector3(tmpx, tmpy, tmpz); 
		 tmpx = cpydouble(p);
		 tmpy = cpydouble(p);
		 tmpz = cpydouble(p);
		 tmp_tri.v1 = Vector3(tmpx, tmpy, tmpz); 
		 tmpx = cpydouble(p);
		 tmpy = cpydouble(p);
		 tmpz = cpydouble(p);
		 tmp_tri.v2 = Vector3(tmpx, tmpy, tmpz);
		 tmp_tri.index = i;
		 res[i] = tmp_tri;
		 p += 2;//跳过尾部标志
	 }
	 module = res;

	 std::ofstream out;
	 out.open("LOG/ReadSTLFile.log");
	 for (i = 0; i < unTriangles; ++i)
	 {
		 out << "TriFace[" << i << "]" << std::endl;
		 out << "\tv0\t(" << module[i].v0.x << "," << module[i].v0.y << "," << module[i].v0.z << ")" << std::endl;
		 out << "\tv1\t(" << module[i].v1.x << "," << module[i].v1.y << "," << module[i].v1.z << ")" << std::endl;
		 out << "\tv2\t(" << module[i].v2.x << "," << module[i].v2.y << "," << module[i].v2.z << ")" << std::endl;
		 out << "\tnormal\t(" << module[i].normal.x << "," << module[i].normal.y << "," << module[i].normal.z << ")" << std::endl;
	 }
	 out << "Total: " << unTriangles << " trifaces" << std::endl;
	 out.close();

	 printf("STL Files loaded.\n");
	 printf("The number of triangles is: %d\n", unTriangles);
	 return true;
 }


 int ReadSTLFile::cpyint(const char*& p)
 {
	 int cpy;
	 memwriter = (char*)&cpy;
	 memcpy(memwriter, p, 4);
	 p += 4;
	 return cpy;
 }

 float ReadSTLFile::cpydouble(const char*& p)
 {
	 float cpy;
	 memwriter = (char*)&cpy;
	 memcpy(memwriter, p, 4);
	 p += 4;
	 return cpy;
 }