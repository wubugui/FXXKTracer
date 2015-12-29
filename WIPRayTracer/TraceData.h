#pragma once
#include "Colorf.h"
#include "BaseGeometryObject.h"
#include "Ray.h"


class TraceData
{
public:
	float tmin;
	BaseGeometryObject* nearest_geo;
	Ray* cur_ray;
	RBColorf color;

	TraceData();
	~TraceData();
};

