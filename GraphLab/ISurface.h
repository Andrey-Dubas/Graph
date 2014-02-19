#pragma once
#include "igrapgentity.h"
#include "GraphicLib.h"
#include "NumProperty.h"
#include "line.h"
class ISurface abstract:
	public IGraphEntity
{
public:
	point normalC;
	point normalOrientation;
protected:
	int amountU;
	int amountV;
public:
	ISurface(int U, int V):amountU(U), amountV(V){
		this->origPos = CordContainer(U, V);
		this->registerClassDescriptor();
	}

	/*ISurface():amountU(20), amountV(20){
		this->registerClassDescriptor();
	}*/
	virtual ~ISurface(void);
	virtual void recalculateInitialData();
protected:
	ADD_PROPERTY_START();
	ADD_PROPERTY(IntProperty, amountU, "U discrete");
	ADD_PROPERTY(IntProperty, amountV, "V discrete");
	ADD_PROPERTY_END();

	bool isPointIn(float x, float y);

	//virtual ElementContainer getDescriptionElements();

	
	virtual point function(float U, float V)=0;
};
