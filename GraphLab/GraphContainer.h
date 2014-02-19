#pragma once
#include "igraphcontainer.h"


class MyQGraphicsView;
template<typename PaintControl>
class GraphContainer :
	public IGraphContainer
{
protected:
	MyQGraphicsView* paintControl;
public:
	virtual void draw()=0;

	GraphContainer(MyQGraphicsView* ctrl){
		paintControl = ctrl;

	}

	const PaintControl* getDevice() const{ return paintControl;}


	~GraphContainer(void){
	}
};
