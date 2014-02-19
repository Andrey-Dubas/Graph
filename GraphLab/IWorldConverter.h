#pragma once
#include "imatrixlayer.h"
#include "GraphicLib.h"
#include "IGraphLayer.h"
#include "NumProperty.h"
#include "InfoProvider.h"
#include "PointProperty.h"
class IWorldConverter abstract:
	public IMatrixLayer 
{
protected:
	point objectPos;
	point objectOrientation;
	point objectSpaceKoef;
public:
	PRIORITY(1);
	SINGLETON(false);

ADD_PROPERTY_START()
	ADD_PROPERTY(PointProperty, objectPos, "position");
	ADD_PROPERTY(PointProperty, objectOrientation, "orientation");
	ADD_PROPERTY(PointProperty, objectSpaceKoef, "Space koef");
ADD_PROPERTY_END()


	IWorldConverter(point pos, point orientation);
	IWorldConverter(void);
	IWorldConverter(const IWorldConverter& obj);
	virtual ~IWorldConverter(void);
};
