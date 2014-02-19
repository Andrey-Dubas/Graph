#pragma once
#include "igraphlayer.h"
#include "graphicLib.h"
class IMatrixLayer abstract:
	public IGraphLayer
{
protected:
	float** matrix;
	float** revMatrix;
protected:
	void computeReverseMatrix(){
		reverseMatrix<4>(matrix, revMatrix);
	}
public:

	virtual void recalculateInitialData(){
		this->preProcessForward();
		this->preProcessBackward();
	}

	virtual void process(){
		preProcessForward();
		for(int i=0; i<this->originalPos->rows; ++i){
			for(int j=0; j<this->originalPos->cols; ++j){
				float v1[4], v2[4]; 
				originalPos->Cords[i][j](v1);
				Mul(matrix, v1, v2);
				convertedPos->Cords[i][j] = point(v2);
			}
		}
	}

	virtual void reverseProcess(){
		preProcessBackward();
		for(int i=0; i<this->originalPos->rows; ++i)
			for(int j=0; j<this->originalPos->cols; ++j){
				float v1[4], v2[4];
				this->originalPos->Cords[i][j](v1);
				Mul(this->revMatrix, v1, v2);
				this->convertedPos->Cords[i][j] = point(v2);
			}
	}

	virtual void preProcessBackward(){
		reverseMatrix<4>(matrix, this->revMatrix);
	}
	
	IMatrixLayer(void)
	{
		matrix = matrixINI<4>();
		revMatrix = matrixINI<4>();
		registerClassDescriptor();
	}

	IMatrixLayer(const IMatrixLayer& obj){
		matrix = matrixINI<4>();
		revMatrix = matrixINI<4>();
		for(int i=0; i<4; ++i){
			for(int j=0; j<4; ++j){
				matrix[i][j] = obj.matrix[i][j];
				revMatrix[i][j] = obj.revMatrix[i][j];
			}
		}
	}

	virtual ~IMatrixLayer(void)
	{
		matrixFREE<4>(matrix);
		matrixFREE<4>(revMatrix);
	}

};
