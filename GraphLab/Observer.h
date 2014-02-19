#pragma once
#include "imatrixlayer.h"
#include "GraphicLib.h"
#include "PointProperty.h"
class Observer :
	public IMatrixLayer
{
public:
	point position;//!!!!!!!!!!!!!!!!!!!!!!!!!
protected:
	
	point orientation;
	float **m1, **m2;
public:
	SINGLETON(true);
	NOT_CLONNABLE;
	PRIORITY(2);

	ADD_PROPERTY_START()//addPropertiesDescriptor 
	//ADD_PROPERTY(PointProperty, position, "position");
	ADD_PROPERTY(PointProperty, position, "position");
	ADD_PROPERTY(PointProperty, orientation, "orientation");
	ADD_PROPERTY_END()

	virtual ~Observer(void);
	Observer(point pos, point ori);

	virtual void preProcessForward();

	void setPosition(point pos);
	void setOrientation(point pos);

private:
	Observer(const Observer& obj);
	const Observer operator=(Observer& obj);
};
