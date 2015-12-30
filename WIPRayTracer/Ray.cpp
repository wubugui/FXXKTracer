#include "Ray.h"


Ray::Ray(float tt)
{
	t = tt;
}


Ray::Ray(RBVector3 o, RBVector3 end)
{
	this->o = o;
	this->direction = (end - o).get_normalized();
	this->t = (end - o).size();
}

Ray::~Ray()
{

}

const Ray Ray::sss(12);

A1::A1(int k)
{
	l = k;
}



const A1 A1::CA(12);