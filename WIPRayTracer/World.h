#pragma once
#include <vector>
#include "..\..\RBMath\Inc\Colorf.h"
#include "..\..\RBMath\Inc\Color32.h"
#include "TraceData.h"
#include "PhongMat.h"

class BaseGeometryObject;
class Ray;

class World
{
public:

	void build(int num);
	void render();

	void out_put();

	World();
	~World();

private:

	RBVector3 _tonemap(RBVector3 x);
	void tone(RBColorf& c);

	PhongMat* phong_mat[4];
	RBVector4 shade(TraceData& _trace_data,bool shadow);
	RBColorf trace_ray(Ray& ray, TraceData& _trace_data,int dep);
	
	unsigned char *_out_image;
	typedef std::vector<BaseGeometryObject*> _ObjectList;
	_ObjectList _objects;

	static const int max_depth = 8;

	RBVector3 light_pos;
};

