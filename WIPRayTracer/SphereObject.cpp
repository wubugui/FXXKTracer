#include "SphereObject.h"
#include "Ray.h"
#include "TraceData.h"
#include "PhongMat.h"

SphereObject::SphereObject() : BaseGeometryObject(1.f,1.f,1.f,1.f)
{
	type = E_Sphere;
}


SphereObject::~SphereObject()
{
}

bool SphereObject::hit(Ray& ray,  TraceData& data) const
{
	float t;
	RBVector3 temp = ray.o - position;
	float a = RBVector3::dot_product(ray.direction, ray.direction);
	float b = 2.f*RBVector3::dot_product(temp, ray.direction);
	float c = RBVector3::dot_product(temp, temp) - r*r;
	float ds = b*b - 4 * a*c;

	if (ds < 0.f)
	{
		return false;
	}
	else
	{
		float e = RBMath::sqrt(ds);
		float de = 2.f * a;
		t = (-b - e) / de;

		if (t > SMALL_F)
		{
			if (t < ray.t)
			{
				ray.t = t;
				data.color = color;
			}
			return true;
		}

		t = (-b + e) / de;

		if (t>SMALL_F)
		{
			if (t < ray.t)
			{
				ray.t = t;
				data.color = color;
			}
			return true;
		}
	}
	return false;
}

RBVector4 SphereObject::shade(RBVector3 n, RBVector3 l,RBVector3 v)
{
	if (!mat) return RBVector4(0,0,0,0);
	return ((PhongMat*)mat)->shade(n, l, v);
}

RBVector3 SphereObject::get_normal(RBVector3 surf_p)
{
	return surf_p - position;
}
