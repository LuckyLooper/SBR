#include<iostream>
#include<fstream>
#include<stdlib.h>

#include"TriFace.h"
#include"Vector3.h"
#include"ReadSTLFile.h"
#include"RayInit.h"
#include"RayTracing.h"

#define PI 3.141592654
#define uZero 1e-6

int main()
{
	system("md LOG");

	float alpha=0;
	float theta_low,theta_high;
	float phi_low,phi_high;
	float theta, phi;
	float nstep;
	float frequency, lambda;

	std::cout << "frequency: ";
	std::cin >> frequency;
	std::cout << std::endl;
	std::cout << "theta_low: ";
	std::cin >> theta_low;
	std::cout << std::endl;
	std::cout << "theta_high: ";
	std::cin >> theta_high;
	std::cout << std::endl;
	std::cout << "phi_low: ";
	std::cin >> phi_low;
	std::cout << std::endl;
	std::cout << "phi_high: ";
	std::cin >> phi_high;
	std::cout << std::endl;
	std::cout << "nstep: ";
	std::cin >> nstep;
	std::cout << std::endl;
	lambda = 0.3 / frequency;

	//打开模型文件
	ReadSTLFile input;
	input.ReadFile("sanmianjiao.STL");

	//创建结果文件
	std::ofstream out_res;
	out_res.open("result.txt");
	out_res << "theta" << " " << "phi" << " " << "rcs_theta" << " " << "rcs_phi" << std::endl;
	out_res.close();

	//射线追踪及计算
	for(float theta_j=theta_low;theta_j<=theta_high;theta_j+=nstep)
		for (float phi_j = phi_low; phi_j <= phi_high; phi_j += nstep)
		{
			theta = theta_j*PI / 180.0;
			phi = phi_j*PI / 180.0;
			RayInit ray_init;
			ray_init.init(&input, 5.0, alpha, theta, phi, lambda);
			RayTracing rt;
			rt.tracing(&input, &ray_init, 3, lambda, theta, phi);			
		}
	
	return 0;
}