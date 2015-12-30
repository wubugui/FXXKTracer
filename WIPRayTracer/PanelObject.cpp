#include "PanelObject.h"
#include "Ray.h"
#include "TraceData.h"
#include "PhongMat.h"

PanelObject::PanelObject():BaseGeometryObject(1.f, 1.f, 1.f, 1.f)
{
	type = E_Panel;
}


PanelObject::~PanelObject()
{
}

bool PanelObject::hit(Ray& ray,  TraceData& data) const
{
	float temp = RBVector3::dot_product(ray.direction, normal);
	if (RBMath::is_nearly_zero(temp)) return false;

	float t = (RBVector3::dot_product(point, normal) - RBVector3::dot_product(ray.o, normal)) / temp;

	if (t>SMALL_F)
	{
		if (t<ray.t)
		{
			ray.t = t;
			data.color = color;
		}
		return true;
	}
	else
	{
		return false;
	}
}

RBVector4 PanelObject::shade(RBVector3 n, RBVector3 l, RBVector3 v,  RBColorf ld)
{
	n = normal;
	if (!mat) return RBVector4(0, 0, 0, 0);
	return ((PhongMat*)mat)->shade(n, l, v,ld);
}

RBVector3 PanelObject::get_normal(RBVector3 surf_p)
{
	return normal;
}
