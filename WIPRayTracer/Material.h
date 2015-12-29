#pragma once
#include  "Vector3.h"

class Material
{
public:
	Material(){}
	~Material(){}

	virtual float f(RBVector3 wi,RBVector3 wo,RBVector3 p = RBVector3::zero_vector) = 0;
	virtual float f_sampling(RBVector3 wi, RBVector3 wo, RBVector3 p = RBVector3::zero_vector) = 0;
private:

};
