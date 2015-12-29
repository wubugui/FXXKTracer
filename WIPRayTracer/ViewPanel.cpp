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
void ViewPanel::emit_ray(int v, int h, Ray& ray, TraceData& data)
{
	//有透视的相机
	pixel_size = 0.003;

	float x = pixel_size*(h-hsize/2+0.5);
	float y = pixel_size*(v - vsize / 2 + 0.5);
	ray.o.x = 0;
	ray.o.y = 0;
	ray.o.z = -1.f;

	ray.direction.x = x;
	ray.direction.y = y;
	ray.direction.z = 1.f;
	ray.direction.normalize();
	
}
