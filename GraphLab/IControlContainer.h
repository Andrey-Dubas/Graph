#pragma once
#include "ObjectDescriptor1.h"
#include <list>

class IControlContainer
{
protected:
	//ObjectDescriptor* currentDescriptor;
public:

	//virtual void setDescriptor(ObjectDescriptor* desc)=0;

	IControlContainer(void)
	{
	}

	virtual ~IControlContainer(void)
	{
	}
};
