#pragma once
#include "isurface.h"


# define DENUM_RATIONAL(AXE)\
	( mass[0]*pointArr[0].AXE*pow(V, 3)*pow((1-V), 0) + 3*mass[1]*pointArr[1].AXE*pow(V, 2)*pow((1-V), 1) + 3*mass[2]*pointArr[2].AXE*pow(V, 1)*pow((1-V), 2) +  mass[3]*pointArr[3].AXE*pow(V, 0)*pow((1-V), 3) ) / (mass[0]*pow(V, 3)*pow((1-V), 0) + 3*mass[1]*pow(V, 2)*pow((1-V), 1) + 3*mass[2]*pow(V, 1)*pow((1-V), 2) +  mass[3]*pow(V, 0)*pow((1-V), 3))
class RationalCurve :
	public ISurface
{
protected:
	point* pointArr;
	float* mass;
	int *koef;//{1, 3, 3, 1}; 
	float length;
	int numElements;
protected:
	ADD_PROPERTY_START();

	for(int i=0; i<numElements; ++i){
		ADD_PROPERTY(PointProperty, pointArr[i], "point");
		ADD_PROPERTY(FloatProperty, mass[i], "mass");
	}
	/*ADD_PROPERTY(PointProperty, pointArr[0], "point1");
	ADD_PROPERTY(PointProperty, pointArr[1], "point2");
	ADD_PROPERTY(PointProperty, pointArr[2], "point3");
	ADD_PROPERTY(PointProperty, pointArr[3], "point4");

	ADD_PROPERTY(FloatProperty, mass[0], "mass1");
	ADD_PROPERTY(FloatProperty, mass[1], "mass2");
	ADD_PROPERTY(FloatProperty, mass[2], "mass3");
	ADD_PROPERTY(FloatProperty, mass[3], "mass4");
	*/

	ADD_PROPERTY(FloatProperty, length, "length");
	ADD_PROPERTY_END();
public:
	virtual point function(float U, float V){
		//int startPoint = V*(numElements-4);
		//int _v = 4/(float)(numElements-4);
		point p;
		U *= 2*3.1415;
		point p1 = getCreativePoint(1-V, 0);
		p.x = p1.x*cos(U);// - p1.y*sin(U);
		p.y = p1.x*sin(U);// + p1.y*cos(U);
		p.z = p1.y;
		return p;
	}

	point getCreativePoint(float V, int num){
		float numeratorX=0;
		float numeratorY=0;
		float denumerator=0;
		float localKoef;
		int elCount = numElements;
		for(int i=num; i<num+elCount; i++){
			localKoef = koef[i+num]*mass[num+i]*pow(V, elCount-1-(i-num))*pow((1-V), i-num);
			numeratorX += localKoef*pointArr[i].x;
			numeratorY += localKoef*pointArr[i].y;
			denumerator+= localKoef;
		}
		return point(numeratorX/denumerator, numeratorY/denumerator, 0);
	}

	RationalCurve(point *_pointArr, float *_mass, int _numElements, float _length, int _amountU, int _amountV):ISurface(_amountU, _amountV), length(_length), numElements(_numElements){
		koef = new int[numElements];
		for(int i=0; i<numElements; ++i){
			koef[i] = pascalKoef(numElements-1, i);
		}

		pointArr = new point[numElements];
		mass = new float[numElements];
		for(int i=0; i<numElements; ++i){
			pointArr[i] = _pointArr[i];
			mass[i] = _mass[i];
		}
		recalculateInitialData();
		this->registerClassDescriptor();
		this->process();
	}

	RationalCurve(point _pointArr[4], float _mass[4], float _length, int _amountU, int _amountV):numElements(4), ISurface(_amountU, _amountV), length(_length){
		numElements = 4;

		koef = new int[numElements];
		for(int i=0; i<numElements; ++i){
			koef[i] = pascalKoef(numElements-1, i);
		}

		pointArr = new point[4];
		mass = new float[4];
		for(int i=0; i<4; ++i){
			pointArr[i] = _pointArr[i];
			mass[i] = _mass[i];
		}
		recalculateInitialData();
		this->registerClassDescriptor();
		this->process();
	}

	~RationalCurve(void){
		delete[] koef;
		delete[] pointArr;
		delete[] mass;
	}
};
