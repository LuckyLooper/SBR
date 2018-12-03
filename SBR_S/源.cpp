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
	float theta_min,theta_max;
	float phi_min,phi_max;
	float theta, phi;
	float nstep;
	float frequency, lambda;

	std::cout << "frequency: ";
	std::cin >> frequency;
	std::cout << std::endl;
	std::cout << "theta_min: ";
	std::cin >> theta_min;
	std::cout << std::endl;
	std::cout << "theta_max: ";
	std::cin >> theta_max;
	std::cout << std::endl;
	std::cout << "phi_min: ";
	std::cin >> phi_min;
	std::cout << std::endl;
	std::cout << "phi_max: ";
	std::cin >> phi_max;
	std::cout << std::endl;
	std::cout << "nstep: ";
	std::cin >> nstep;
	std::cout << std::endl;
	lambda = 0.3 / frequency;

	//打开模型文件
	ReadSTLFile input;
	input.ReadFile("qiuti.STL");

	//创建结果文件
	std::ofstream out_res;
	out_res.open("result.txt");
	out_res << "theta" << " " << "phi" << " " << "rcs_theta" << " " << "rcs_phi" << std::endl;
	out_res.close();

	//射线追踪及计算
	for(float theta_j=theta_min;theta_j<=theta_max;theta_j+=nstep)
		for (float phi_j = phi_min; phi_j <= phi_max; phi_j += nstep)
		{
			theta = theta_j*PI / 180.0;
			phi = phi_j*PI / 180.0;
			RayInit ray_init;
			ray_init.init(&input, 5.0, alpha, theta, phi, lambda);
			RayTracing rt;
			rt.tracing(&input, &ray_init, 10, lambda, theta, phi);			
		}
	
	return 0;
}