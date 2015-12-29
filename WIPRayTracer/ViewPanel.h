#pragma once

class Ray;
class TraceData;
class ViewPanel
{
public:
	int vsize;
	int hsize;
	float pixel_size;

	void emit_ray(int v,int h,Ray& ray,TraceData& data);

	ViewPanel(int vsize = 100,int hsize = 100,float pixel_size = 1.0);

	float f;
	~ViewPanel();
};

