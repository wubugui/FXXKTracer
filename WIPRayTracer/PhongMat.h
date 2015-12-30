#pragma once

#include "Material.h"
#include "RBMath.h"
#include "Vector3.h"

class PhongMat :public Material
{
public:
	PhongMat();
	~PhongMat();
	float f(RBVector3 wi, RBVector3 wo, RBVector3 p = RBVector3::zero_vector) override;
	float f_sampling(RBVector3 wi, RBVector3 wo, RBVector3 p = RBVector3::zero_vector) override;
	 //漫反射系数
	 float kd;
	 //材质颜色
	 RBVector3 cd;
	 //高光系数
	 float kspec;
	 //高光颜色
	 RBVector3 cs;
	 RBVector4 shade(RBVector3 n, RBVector3 l, RBVector3 v, RBColorf ld);
private:

};

