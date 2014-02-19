#pragma once
#include "ilayerfactory.h"
#include "IGraphLayer.h"

class TestLayerFactory :
	public ILayerFactory
{
public:

	virtual const std::list<IGraphLayer*>& getSingletonLayers()const{
		return this->stackLayer;
	}

	virtual IWorldConverter* getWorldConverter(point pos, point orientation)const{
		return new EvclidConverter(pos, orientation);
	}

	TestLayerFactory(void)
	{
	}

	virtual ~TestLayerFactory(void)
	{
	}
};
