#include "Conus.h"

Conus::~Conus(void)
{
}

point Conus::function(float U, float V){
	point p;
	p.x = U*R*cos(V*2*3.1415);
	p.y = U*R*sin(V*2*3.1415);
	p.z = H*U;
	return p;
}
