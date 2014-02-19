#pragma once

#include "GraphicLib.h"

class IGraphLib abstract
{
public:
	virtual void draw()=0;
	virtual void additionalInfo()=0;
	point localSpace;
	vector orientation;
	IGraphLib(void);
	virtual ~IGraphLib(void);
};
