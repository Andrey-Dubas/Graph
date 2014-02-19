#pragma once
#include "iworldconverter.h"
#include "InfoProvider.h"
#include "graphicLib.h"
class EvclidConverter :
	public IWorldConverter
{
protected:
	float **m1, **m2;
public:

	ADD_PROPERTY_START()
	ADD_PROPERTY_END();
	PRIORITY(1);

	virtual IGraphLayer* clone(){
		
		EvclidConverter* result = new EvclidConverter(this->objectPos, this->objectOrientation);
		result->preProcessForward();
		//result->preProcessBackward();
		//this-
		Mul(m1, m2, this->matrix);
		return result;
	}

	
	/*EvclidConverter(EvclidConverter obj):IWorldConverter(obj.pos, obj.orientation){
		m1 = matrixINIWithDiag<4>();
		m2 = matrixINIWithDiag<4>();
		registerClassDescriptor();
	}*/

	EvclidConverter(point pos, point orientation):IWorldConverter(pos, orientation){
		m1 = matrixINIWithDiag<4>();
		m2 = matrixINIWithDiag<4>();
		preProcessForward();
		registerClassDescriptor();
	}

	virtual ~EvclidConverter(void)
	{
	}

	virtual void preProcessForward(){
		//float** m1 = matrixINIWithDiag<4>(), **m2 = matrixINIWithDiag<4>();

		Evclid::rotateMatrix(m1, this->objectOrientation);
		Evclid::moveMatrix(m2, this->objectPos);
		Mul(m2, m1, this->matrix);

		//matrixFREE<4>(m1); matrixFREE<4>(m2);
	}

	virtual void process(){
		float** r1 = matrixINIWithDiag<4>(), **r2 = matrixINIWithDiag<4>();
		//matrix
		preProcessForward();
		for(int i=0; i<this->originalPos->rows; ++i){
			for(int j=0; j<this->originalPos->cols; ++j){
				float v1[4], v2[4]; 
				originalPos->Cords[i][j](v1);
				Mul(matrix, m2, m1);
				//Mul(r2, r1, m2);
				Mul(matrix, v1, v2);
				convertedPos->Cords[i][j] = point(v2);
			}
		}
		matrixFREE<4>(r1);
		matrixFREE<4>(r2);
	}
	
};
