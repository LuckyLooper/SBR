#include "RayTracing.h"
#include<fstream>


#define uZero 1e-6
#define PI 3.141592654

bool RayTracing::isIntersect_N(ReadSTLFile * input, NRay * ray)
{
	bool res = false;
	float t0 = FLT_MAX;
	unsigned long index = 0;//用于记录相交的面元编号
	Ray ray_tmp;
	ray_tmp.direction = ray->direction;
	ray_tmp.origin = ray->origin;
	for (unsigned long i = 0; i < input->unTriangles; ++i)
	{
		//如果光线与面元法线的夹角范围为(0,90)，则该面元与光线不相交
		if (ray->direction.dot_product(input->module[i].normal) >= 0)
			continue;

		//判断光线与面元是否相交，
		//若相交，则将返回值置为true，否则与下一个面元做相交检测
		Vector3 edge1, edge2;
		float u, v, t;
		edge1 = input->module[i].v1 - input->module[i].v0;
		edge2 = input->module[i].v2 - input->module[i].v0;
		Vector3 pvec;
		pvec = (ray->direction).cross_product(edge2);
		float det;
		det = edge1.dot_product(pvec);
		Vector3 tvec = ray->origin - input->module[i].v0;
		if (det < 0.0)
			continue;
		u = tvec.dot_product(pvec);
		if (u<0.0 || u>det)
			continue;
		Vector3 qvec;
		qvec = tvec.cross_product(edge1);
		v = (ray->direction).dot_product(qvec);
		if (v<0.0 || u + v>det)
			continue;
		t = edge2.dot_product(qvec);
		if (t <= 0.0)
			continue;
		float invdet = 1.0 / det;
		t *= invdet;
		u *= invdet;
		v *= invdet;
		res = true;

		//判断多重遮挡,若出现多重遮挡则将此时的反射光线暂存在临时值ray_tmp
		if (t < t0)
		{
			t0 = t;
			index = i;
			ray_tmp.origin = (input->module[i].v0)*(1.0 - u - v)
				+ (input->module[i].v1)*u
				+ (input->module[i].v2)*v;
			ray_tmp.direction = ray->direction
				- (input->module[i].normal)*(2.0 * ((ray->direction).dot_product(input->module[i].normal)));

		}
	}


	//若无相交的面元，则入射光线不变，返回值为false
	if (res == false)return res;

	//若有相交的面元，入射光线更新为反射光线
	ray->direction = ray_tmp.direction;
	ray->origin = ray_tmp.origin;
	ray->index = index;
	if (res == true)++ray->count;

	return res;
}

bool RayTracing::isIntersect_C(ReadSTLFile * input, CRay * ray, float lambda)
{
	bool res = false;
	float t0 = FLT_MAX;
	CRay ray_tmp;
	ray_tmp.direction = ray->direction;
	ray_tmp.origin = ray->origin;
	unsigned long index = 0;//用于记录相交的面元编号
	for (unsigned long i = 0; i < input->unTriangles; ++i)
	{
		//如果光线与面元法线的夹角范围为(0,90)，则该面元与光线不相交
		if (ray->direction.dot_product(input->module[i].normal) >= 0)
			continue;

		//判断光线与面元是否相交，
		//若相交，则将返回值置为true，否则与下一个面元做相交检测
		Vector3 edge1, edge2;
		float u, v, t;
		edge1 = input->module[i].v1 - input->module[i].v0;
		edge2 = input->module[i].v2 - input->module[i].v0;
		Vector3 pvec;
		pvec = (ray->direction).cross_product(edge2);
		float det;
		det = edge1.dot_product(pvec);
		Vector3 tvec = ray->origin - input->module[i].v0;
		if (det < 0.0)
			continue;
		u = tvec.dot_product(pvec);
		if (u<0.0 || u>det)
			continue;
		Vector3 qvec;
		qvec = tvec.cross_product(edge1);
		v = (ray->direction).dot_product(qvec);
		if (v<0.0 || u + v>det)
			continue;
		t = edge2.dot_product(qvec);
		if (t <= 0.0)
			continue;
		float invdet = 1.0 / det;
		t *= invdet;
		u *= invdet;
		v *= invdet;
		res = true;

		//判断多重遮挡,若出现多重遮挡则将此时的反射光线暂存在临时值ray_tmp
		if (t < t0)
		{
			t0 = t;
			index = i;
			ray_tmp.origin = (input->module[index].v0)*(1.0 - u - v)
				+ (input->module[index].v1)*u
				+ (input->module[index].v2)*v;
			ray_tmp.direction = ray->direction
				- (input->module[index].normal)*(2.0 * ((ray->direction).dot_product(input->module[index].normal)));

		}
	}

	//若无相交的面元，则入射光线不变，返回值为false
	if (res == false)
		return res;
	//若有相交的面元，入射光线更新为反射光线，同时更新场强
	else
	{
		//更新相交的面元
		ray->index = index;

		//更新电场幅度变化
		Vector3 Er;
		Vector3 tn = input->module[index].normal;
		if ((ray->direction.cross_product(tn)).length() < uZero)//当垂直入射时，Er=-Ei，避免后面的除0
		{
			Vector3 vzero(0.0, 0.0, 0.0);
			Er = vzero - ray->Ei;
		}
		else
		{
			/*Vector3 reflect = ray_tmp.direction;
			Vector3 eivv = (ray->direction.cross_product(tn)).normalize();
			Vector3 eihh = (ray->direction.cross_product(eivv)).normalize();
			Vector3 ervv = eivv;
			Vector3 erhh = (reflect.cross_product(ervv)).normalize();
			float EiVV = eivv.dot_product(ray->Es);
			float EiHH = eihh.dot_product(ray->Es);
			float ErVV = -1.0*EiVV;
			float ErHH = EiHH;
			Er = ervv*ErVV + erhh*ErHH;*/

			Vector3 Evv = tn*(ray->Es.dot_product(tn));
			Vector3 Ehh = ray->Es - Evv;
			Er = Evv - Ehh;
		}
		ray->Ei = ray->Es;
		ray->Es = Er;

		//更新射线总路程
		ray->distance += (ray_tmp.origin - ray->origin).length();

		//更新入射和反射光线
		ray->in_dir = ray->direction;
		ray->origin = ray_tmp.origin;
		ray->direction = ray_tmp.direction;

		return res;
	}
}

void RayTracing::routine_N(ReadSTLFile * input, NRay * ray, int max_reflect)
{
	int i = 0;
	//达到最大反射次数或出现不相交情况，停止相交检测
	while (i < max_reflect)
	{
		if (isIntersect_N(input, ray) == false)
			break;
		++i;
	}
}

void RayTracing::routine_C(ReadSTLFile * input, CRay * ray, int max_reflect, float lambda)
{
	int i = 0;
	//达到最大反射次数或出现不相交情况，停止相交检测
	while (i < max_reflect)
	{
		if (isIntersect_C(input, ray, lambda) == false)
			break;
		++i;
	}
}

void RayTracing::tracing(ReadSTLFile * input, RayInit * rays, int max_reflect, float lambda, float theta, float phi)
{
	//对周围的四根射线进行追踪
	for (unsigned long i = 0; i < rays->rows + 1; ++i)
		for (unsigned long j = 0; j < rays->columns + 1; ++j)
		{
			routine_N(input, &(rays->NRays[i][j]), max_reflect);
		}

	//对中心射线进行追踪
	for (unsigned long i = 0; i < rays->rows; ++i)
		for (unsigned long j = 0; j < rays->columns; ++j)
			routine_C(input, &(rays->CRays[i][j]), max_reflect, lambda);

	/*记录射线的出射点及方向，方便确认射线追踪是否正确*/
	/*std::ofstream out_count;
	out_count.open("ray_out.txt");
	for (unsigned long i = 0; i<rays->rows ; ++i)
		for (unsigned long j = 0; j < rays->columns ; ++j)
		{
			if (rays->NRays[i][j].count > 0)
			{
				Vector3 end = rays->CRays[i][j].origin - rays->CRays[i][j].in_dir*2.0;
				out_count <<
					end.x << " " <<
					end.y << " " <<
					end.z << " "<<
					rays->CRays[i][j].origin.x << " " <<
					rays->CRays[i][j].origin.y << " " <<
					rays->CRays[i][j].origin.z << " " <<
					std::endl;
			}

		}
	out_count.close();*/

	double k0 = 2.0*PI / lambda;
	float area1, area2;//一根射线管决定一个出射四边形面，也就是两个三角形面积
	Vector3 thetaDir(cos(theta)*cos(phi), cos(theta)*sin(phi), -sin(theta));
	Vector3 phiDir(-sin(phi), cos(phi), 0);
	Vector3 scatterDir(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));
	Complexf Es_theta(0.0, 0.0);
	Complexf Es_phi(0.0, 0.0);
	Complexf IntegralTempPhi(0.0, 0.0);
	Complexf IntegralTempTheta(0.0, 0.0);
	Complexf IntegralPhi(0.0, 0.0);
	Complexf IntegralTheta(0.0, 0.0);
	Complexf cj(0.0, 1.0);
	float rcs_theta = 0.0;
	float rcs_phi = 0.0;

	for (unsigned long i = 0; i < rays->rows; ++i)
		for (unsigned long j = 0; j < rays->columns; ++j)
		{
			//若相交次数为0，则不用求和，
			//若周围的四根射线相交次数不等，则射线管分裂
			if (rays->NRays[i][j].count == 0 ||
				rays->NRays[i][j].count != rays->NRays[i + 1][j].count ||
				rays->NRays[i][j].count != rays->NRays[i][j + 1].count ||
				rays->NRays[i][j].count != rays->NRays[i + 1][j + 1].count)
				continue;

			//射线管所有角点射线出射点所组成四边形的对角线长度不能超过一定值，否则认定射线管分裂
			if (abs((rays->NRays[i][j].origin - rays->NRays[i + 1][j + 1].origin).length() -
				(rays->NRays[i + 1][j].origin - rays->NRays[i][j + 1].origin).length()) > 2 * lambda)
				continue;

			Vector3 v[4];
			Vector3 vc;
			Vector3 side[4];
			Vector3 NorDir;
			Vector3 FacetNormalc = input->module[rays->CRays[i][j].index].normal;
			Vector3 stopPointc = rays->CRays[i][j].origin;
			Vector3 ei = rays->CRays[i][j].Ei;
			//一根射线管管一个四边形出射面元
			Vector3 point1[7], point2[7];
			float Weight[7] = { 9.0 / 80,(155 - sqrt(15.0)) / 2400,(155 - sqrt(15.0)) / 2400,(155 - sqrt(15.0)) / 2400,(155 + sqrt(15.0)) / 2400,(155 + sqrt(15.0)) / 2400,(155 + sqrt(15.0)) / 2400 };

			v[0] = rays->NRays[i][j].origin;
			v[1] = rays->NRays[i+1][j].origin;
			v[2] = rays->NRays[i+1][j+1].origin;
			v[3] = rays->NRays[i][j+1].origin;
			vc = rays->CRays[i][j].origin;

			side[0] = v[1] - v[0];
			side[1] = v[2] - v[1];
			side[2] = v[3] - v[2];
			side[3] = v[0] - v[3];

			NorDir = (side[0] ^ side[1]).normalize();
			if (NorDir * FacetNormalc < 0)
			{
				NorDir = -NorDir;
			}

			area1 = (side[0]^ (v[2]-v[0])).length() / 2.0;
			area2 = (side[2] ^ (v[0] - v[2])).length() / 2.0;

			point1[0] = (v[0] + v[1] + v[2]) / 3.0;
			point1[1] = ((6.0 - sqrt(15.0)) / 21.0) * v[0] + ((6.0 - sqrt(15.0)) / 21.0) * v[1] + (1.0 - 2 * ((6.0 - sqrt(15.0)) / 21.0)) * v[3];
			point1[2] = ((6.0 - sqrt(15.0)) / 21.0) * v[0] + ((9.0 + 2 * sqrt(15.0)) / 21.0) * v[1] + (1.0 - ((6.0 - sqrt(15.0)) / 21.0) - ((9.0 + 2 * sqrt(15.0)) / 21.0)) * v[3];
			point1[3] = ((9.0 + 2 * sqrt(15.0)) / 21.0) * v[0] + ((6.0 - sqrt(15.0)) / 21.0) * v[1] + (1.0 - ((6.0 - sqrt(15.0)) / 21.0) - ((9.0 + 2 * sqrt(15.0)) / 21.0)) * v[3];
			point1[4] = ((6.0 + sqrt(15.0)) / 21.0) * v[0] + ((6.0 + sqrt(15.0)) / 21.0) * v[1] + (1.0 - 2 * ((6.0 + sqrt(15.0)) / 21.0)) * v[3];
			point1[5] = ((6.0 + sqrt(15.0)) / 21.0) * v[0] + ((9.0 - 2 * sqrt(15.0)) / 21.0) * v[1] + (1.0 - ((6.0 + sqrt(15.0)) / 21.0) - ((9.0 - 2 * sqrt(15.0)) / 21.0)) * v[3];
			point1[6] = ((9.0 - 2 * sqrt(15.0)) / 21.0) * v[0] + ((6.0 + sqrt(15.0)) / 21.0) * v[1] + (1.0 - ((6.0 + sqrt(15.0)) / 21.0) - ((9.0 - 2 * sqrt(15.0)) / 21.0)) * v[3];

			point2[0] = (v[2] + v[3] + v[0]) / 3.0;
			point2[1] = ((6.0 - sqrt(15.0)) / 21.0) * v[0] + ((6.0 - sqrt(15.0)) / 21.0) * v[3] + (1.0 - 2 * ((6.0 - sqrt(15.0)) / 21.0)) * v[2];
			point2[2] = ((6.0 - sqrt(15.0)) / 21.0) * v[0] + ((9.0 + 2 * sqrt(15.0)) / 21.0) * v[3] + (1.0 - ((6.0 - sqrt(15.0)) / 21.0) - ((9.0 + 2 * sqrt(15.0)) / 21.0)) * v[2];
			point2[3] = ((9.0 + 2 * sqrt(15.0)) / 21.0) * v[0] + ((6.0 - sqrt(15.0)) / 21.0) * v[3] + (1.0 - ((6.0 - sqrt(15.0)) / 21.0) - ((9.0 + 2 * sqrt(15.0)) / 21.0))* v[2];
			point2[4] = ((6.0 + sqrt(15.0)) / 21.0) * v[0] + ((6.0 + sqrt(15.0)) / 21.0) * v[3] + (1.0 - 2 * ((6.0 + sqrt(15.0)) / 21.0)) * v[2];
			point2[5] = ((6.0 + sqrt(15.0)) / 21.0) * v[0] + ((9.0 - 2 * sqrt(15.0)) / 21.0) * v[3] + (1.0 - ((6.0 + sqrt(15.0)) / 21.0) - ((9.0 - 2 * sqrt(15.0)) / 21.0)) * v[2];
			point2[6] = ((9.0 - 2 * sqrt(15.0)) / 21.0) * v[0] + ((6.0 + sqrt(15.0)) / 21.0) * v[3] + (1.0 - ((6.0 + sqrt(15.0)) / 21.0) - ((9.0 - 2 * sqrt(15.0)) / 21.0)) * v[2];

			//part5
			Complexf expTemp1;
			Complexf expTemp2;
			Complexf IntegralTemp1(0.0, 0.0);
			Complexf IntegralTemp2(0.0, 0.0);
			//part4
			Vector3 TempCVector1;
			Vector3 TempCVector2;
			//part3
			Vector3 IncDir = rays->CRays[i][j].in_dir;
			Complexf exptemp = exp(cj * k0 * (IncDir * stopPointc));

			//准备积分5
			for (int kk = 0; kk <= 6; kk++)
			{
				expTemp1 = exp(cj * k0 * ((scatterDir - IncDir) * point1[kk]));
				IntegralTemp1 = IntegralTemp1 + Weight[kk] * expTemp1;
			}
			for (int kk = 0; kk <= 6; kk++)
			{
				expTemp2 = exp(cj * k0 * ((scatterDir - IncDir) * point2[kk]));
				IntegralTemp2 = IntegralTemp2 + Weight[kk] * expTemp2;
			}
			IntegralTemp1 = 2.0 * area1 * IntegralTemp1;
			IntegralTemp2 = 2.0 * area2 * IntegralTemp2;
			//准备矢量乘4
			TempCVector1 = scatterDir ^ (scatterDir ^ (NorDir ^ (IncDir^ei)));
			TempCVector2 = scatterDir ^ (ei ^ NorDir);


			//平行极化求和
			IntegralTempPhi = exp(-cj*k0*rays->CRays[i][j].distance) * exptemp * ((TempCVector1 - TempCVector2)*phiDir) * (IntegralTemp1 + IntegralTemp2);
			IntegralPhi = IntegralPhi + IntegralTempPhi;
			//垂直极化求和  
			IntegralTempTheta = exp(-cj*k0*rays->CRays[i][j].distance) * exptemp * ((TempCVector1 - TempCVector2)*thetaDir) * (IntegralTemp1 + IntegralTemp2);
			IntegralTheta = IntegralTheta + IntegralTempTheta;
		}

	Es_phi = cj * IntegralPhi / (2.0 * lambda);
	Es_theta = cj*IntegralTheta / (2.0*lambda);
	rcs_phi = 4.0*PI*abs(Es_phi)*abs(Es_phi);
	rcs_phi = 10.0*log10(rcs_phi);
	rcs_theta = 4.0*PI*abs(Es_theta)*abs(Es_theta);
	rcs_theta = 10.0*log10(rcs_theta);

	printf("%f %f %f %f\n", theta*180.0 / PI, phi*180.0 / PI, rcs_theta, rcs_phi);
	std::ofstream out_res;
	out_res.open("result.txt", std::ios::app);
	out_res << theta*180.0 / PI << " " << phi*180.0 / PI << " " << rcs_theta << " " << rcs_phi << std::endl;
	out_res.close();
}
