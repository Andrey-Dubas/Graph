#pragma once
#include "isurface.h"

class Conus :
	public ISurface
{
protected:
	float R, H;
public:


	virtual point function(float U, float V);
	Conus(float radius, float height, int U, int V):ISurface(U, V), R(radius), H(height){
		recalculateInitialData();
		this->registerClassDescriptor();
		this->process();
	}
	virtual ~Conus(void);
protected:
	ADD_PROPERTY_START();
	ADD_PROPERTY(FloatProperty, R, "R");
	ADD_PROPERTY(FloatProperty, H, "H");
	ADD_PROPERTY_END();
};
