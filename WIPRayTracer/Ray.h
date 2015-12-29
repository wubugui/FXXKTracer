#pragma once

#include "..\..\RBMath\Inc\Vector3.h"
/*
l = origin + t*direction
*/

class BaseGeometryObject;
class TraceData;
class Ray
{
public:

	RBVector3 o;
	RBVector3 direction;
	float t;

	bool hit(BaseGeometryObject* s,TraceData* data);

	Ray(float t = MAX_F);
	~Ray();

	static const Ray sss;
};

class A1
{
public:
	int l;
	A1(int k);
	static const A1 CA;
};