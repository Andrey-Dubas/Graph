#pragma once
#include "ilayerfactory.h"
#include "EvclidConverter.h"
#include "IGraphLayer.h"
#include "Observer.h"
#include "TrimeterConverter.h"
//#include "RayAngorythm.h"

#include <list>

class LayerFactory :
	public ILayerFactory
{
private:
	std::list<IGraphLayer*> stackLayer;
	
public:
	//static RayAngorythm* ray;
	virtual const std::list<IGraphLayer*>& getSingletonLayers()const{
		return this->stackLayer;
	}

	virtual IWorldConverter* getWorldConverter(point pos, point orientation) const{
		return new EvclidConverter(pos, orientation);
	}

	LayerFactory(void)
	{
		stackLayer.push_front(new Observer(point(200, 350, -600), point(3.14/4., 1, 0)));
		stackLayer.push_front(new TrimeterConverter(point(0, 1.55, 1), point(1, 1, 0)));
		//stackLayer.push_front(ray = new RayAngorythm(1000, 700));
	}

	virtual ~LayerFactory(void)
	{
	}
};

//const static RayAngorythm* ray = 0;
