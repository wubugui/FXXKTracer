#include "Camera.h"

void Camera::compute_uvw()
{
	w = eye_position - target_position;
	w.normalize();
	u = up_dir^w;
	u.normalize();
	v = w^u;
	//sin 90 = 1 所以不需要再正交化
}

