#include "BaseGeometryObject.h"


BaseGeometryObject::BaseGeometryObject(RBColorf color)
{
	this->color = color;
	type = E_GEO;
}

BaseGeometryObject::BaseGeometryObject(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.r = 1.f;
	type = E_GEO;
}

BaseGeometryObject::BaseGeometryObject(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.r = r;

	type = E_GEO;
}


BaseGeometryObject::~BaseGeometryObject()
{
}
