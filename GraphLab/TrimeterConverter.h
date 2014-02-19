#pragma once
#include "imatrixlayer.h"
#include "PointProperty.h"

class TrimeterConverter :
	public IMatrixLayer
{
protected:
	point rayOrientation;
	point angles;
	float** mRay;
	float** mAngles;
public:
	SINGLETON(true);
	NOT_CLONNABLE;

	TrimeterConverter(point ray, point proection):rayOrientation(ray), angles(proection){
		mRay = matrixINIWithDiag<4>();
		mAngles = matrixINIWithDiag<4>();
		registerClassDescriptor();
	}
	virtual void preProcessForward(){
		//float** m1 = matrixINIWithDiag<4>(), **m2 = matrixINIWithDiag<4>();

		float koef = 2 + 1./tan(sqrt(rayOrientation.x*rayOrientation.x + rayOrientation.y*rayOrientation.y));
		float prevKoef = angles.x + angles.y + angles.z;
		angles *= koef/prevKoef;
		//koef = prevKoef;
		//Evclid::rotateMatrix(mRay, rayOrientation);
		//Evclid::moveMatrix(mAngles, angles);
		Evclid::rotateMatrix(mAngles, angles);
		//mAngles[2][2]=0;
		Mul(mAngles, mRay, this->matrix);

		//matrixFREE<4>(m1); matrixFREE<4>(m2);
	}

	ADD_PROPERTY_START();
	ADD_PROPERTY(PointProperty, rayOrientation, "proective beam");
	ADD_PROPERTY(PointProperty, angles, "proetive angle");
	ADD_PROPERTY_END();


	TrimeterConverter(void);
	virtual ~TrimeterConverter(void){
		matrixFREE<4>(mRay);
		matrixFREE<4>(mAngles);
	}

	virtual void process(){
		float** r1 = matrixINIWithDiag<4>(), **r2 = matrixINIWithDiag<4>();
		//matrix
		preProcessForward();
		for(int i=0; i<this->originalPos->rows; ++i){
			for(int j=0; j<this->originalPos->cols; ++j){
				float v1[4], v2[4]; 
				originalPos->Cords[i][j](v1);
				Mul(matrix, mRay, mAngles);
				Mul(matrix, v1, v2);
				convertedPos->Cords[i][j] = point(v2);
			}
		}
		matrixFREE<4>(r1);
		matrixFREE<4>(r2);
	}
};
