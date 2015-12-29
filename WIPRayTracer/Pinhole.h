#pragma once
#include "Camera.h"

class Pinhole : public Camera
{
public:
	RBVector3 ray_direction(const RBVector2& p) const;
	virtual void render_scene(World& w);
protected:

private:
	float view_panel_dis;
	float zoom;
};
