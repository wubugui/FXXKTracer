#pragma once
#include "Vector3.h"

class World;

//”“ ÷œµ
class Camera
{
public:
	RBVector3 eye_position;
	RBVector3 target_position;
	RBVector3 up_dir;
	//float view_panel_dis;
	RBVector3 u, v, w;
	float exposure_time;

	void compute_uvw();
	virtual void render_scene(World& w) = 0;
protected:

private:

};