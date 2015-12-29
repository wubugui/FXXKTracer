#include "PhongMat.h"

PhongMat::PhongMat()
{
}

PhongMat::~PhongMat()
{
}

float PhongMat::f(RBVector3 wi, RBVector3 wo, RBVector3 p)
{
	return INV_PI;
}

float PhongMat::f_sampling(RBVector3 wi, RBVector3 wo, RBVector3 p)
{
	return INV_PI;
}

RBVector4 PhongMat::shade(RBVector3 n, RBVector3 l, RBVector3 v)
{
	n.normalize();
	l.normalize();
	RBVector3 half = v + l;
	half.normalize();

	float cost = RBVector3::dot_product(half, n);

	if (cost < 0) return RBVector4::zero_vector;

	float brdf = f(l, v);
	RBVector3 diff = cd*kd*brdf;
	RBVector3 spec = cs*RBMath::pow(cost, kspec);

	RBVector4 oc = RBVector4(diff + spec, 1.f);

	return oc;

}