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
	 //������ϵ��
	 float kd;
	 //������ɫ
	 RBVector3 cd;
	 //�߹�ϵ��
	 float kspec;
	 //�߹���ɫ
	 RBVector3 cs;
	 RBVector4 shade(RBVector3 n, RBVector3 l, RBVector3 v, RBColorf ld);
private:

};

