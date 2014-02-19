#pragma once
#include "EvclidConverter.h"
#include "IGraphLayer.h"
#include <stack>
#include "IWorldConverter.h"
#include "GraphicLib.h"

typedef std::list<IGraphLayer*> LayerContainer;

class ILayerFactory
{
protected:
	LayerContainer stackLayer;
public:
	virtual const std::list<IGraphLayer*>& getSingletonLayers()const=0;

	virtual IWorldConverter* getWorldConverter(point pos, point orientation) const =0;

	ILayerFactory(void)
	{
		//add 
	}



	virtual ~ILayerFactory(void)
	{
		IGraphLayer* gr;

		LayerContainer::iterator it = stackLayer.begin();
		for(; it!=stackLayer.end(); it++){
			delete *it;
		}
			
	}
};
