#include "ViewPanel.h"
#include "TraceData.h"
#include "Ray.h"


ViewPanel::ViewPanel(int vsize /*= 100*/, int hsize /*= 100*/, float pixel_size /*= 1.0*/)
	:vsize(vsize), hsize(hsize), pixel_size(pixel_size)
{
	f = 1.f;
}


ViewPanel::~ViewPanel()
{

}

//left bottom
void ViewPanel::emit_ray(float v, float h, Ray& ray, TraceData& data)
{
	//有透视的相机
	pixel_size = 0.0015;

	//fov 大约90度1.9
	float f = 2.f;

	float x = pixel_size*(h-hsize/2+0.5);
	float y = pixel_size*(v - vsize / 2 + 0.5);
	ray.o.x = 0;
	ray.o.y = 0.5;
	ray.o.z = -f;

	ray.direction.x = x;
	ray.direction.y = y;
	ray.direction.z = f;
	ray.direction.normalize();
	
}
