#pragma once
#include "BaseGeometryObject.h"
#include "Vector3.h"

class SphereObject : public BaseGeometryObject
{
public:

	float r;
	RBVector3 position;

	virtual bool hit(Ray& ray,TraceData& data) const;
	RBVector4 shade(RBVector3 n, RBVector3 l, RBVector3 v) override;
	RBVector3 get_normal(RBVector3 surf_p);
	SphereObject();
	~SphereObject();
};

