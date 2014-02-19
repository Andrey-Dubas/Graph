#pragma once
#include "igrapgEntity.h"
#include "EvclidConverter.h"
#include "LayerGenerator.h"
#include "NumProperty.h"
#include "graphicLib.h"

class Line :
	public IGraphEntity
{
protected:
	float length;
	point orientation;
public:

	ADD_PROPERTY_START()//addPropertiesDescriptor 
	ADD_PROPERTY(FloatProperty, length, "length");
	ADD_PROPERTY(PointProperty, orientation, "orientation");
	ADD_PROPERTY_END()

	virtual void recalculateInitialData() override{
		point* p1 = &(origPos.Cords[0][0]);
		point* p2 = &(origPos.Cords[0][1]);

		//*p1 = *p1 + point(length*cos(orientation.x)/2., length*cos(orientation.y)/2., length*cos(orientation.z)/2.);
		//*p2 =*p1 + (-point(length*cos(orientation.x)/2., length*cos(orientation.y)/2., length*cos(orientation.z)/2.));
	}

	Line(const Line& obj):IGraphEntity((IGraphEntity&)obj){
		this->length = obj.length;
		this->process();
	}

	Line(float len, point ori): length(len), orientation(ori)
	{
		init();
		recalculateInitialData();

		this->registerClassDescriptor();
		this->process();
	}

	Line(point p1, point p2, LayerContainer l)
	{
		this->convertedPos = new CordContainer(1, 2);

		this->convertedPos->Cords[0][0] = p1;
		this->convertedPos->Cords[0][1] = p2;
		this->LayerStack = l;
		reverseProcess();

	}


	virtual bool isPointIn(float x, float y){
		point p1 = this->convertedPos->Cords[0][0];
		point p2 = this->convertedPos->Cords[0][1];
		if((x>=p1.x&&x<=p2.x)&&(y<=p1.y&&y>=p2.y)){
			return true;
		}
		return false;
	}

	void init(){
		this->origPos.rows = 1;
		this->origPos.cols = 2;

		this->origPos.Cords = new point*[1];
		this->origPos.Cords[0] = new point[2];
		
	}

	virtual ~Line(void)
	{
	}
};
