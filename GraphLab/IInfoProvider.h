#pragma once
#include <vector>
#include "IGraphProperty.h"
#include "ObjectDescriptor1.h"


/*
class for providing messaging within coded attributes
*/
class IInfoProvider
{
protected:
	ObjectDescriptor containedObjects;
	//ObjectDescriptor PreviousObjects;
public:
	virtual std::vector<IGraphProperty*> getParams()=0;//{return std::vector<IGraphProperty*>()};
	virtual void setParam(IGraphProperty*)=0;
	IInfoProvider(void);
	virtual ~IInfoProvider(void);
};
