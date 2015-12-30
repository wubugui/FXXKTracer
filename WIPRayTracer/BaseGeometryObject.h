#pragma once
#include "Colorf.h"
#include "Vector3.h"

class Ray;
class TraceData;
class Material;

enum  GeoTypes
{
	E_GEO,
	E_Panel,
	E_Sphere,
	E_TOTAL
};

class BaseGeometryObject
{
public:

	BaseGeometryObject(RBColorf color);
	BaseGeometryObject(float r,float g,float b);
	BaseGeometryObject(float r, float g, float b,float a);
	~BaseGeometryObject();

	virtual bool hit(Ray& ray,TraceData& data) const = 0;
	virtual RBVector4 shade(RBVector3 n, RBVector3 l, RBVector3 v,  RBColorf ld) = 0;
	virtual RBVector3 get_normal(RBVector3 surf_p) = 0;
	GeoTypes type;
	Material* mat;

	RBColorf color;
};

