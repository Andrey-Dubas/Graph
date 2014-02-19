#pragma once
#include "imatrixlayer.h"
#include "GraphicLib.h"

class EyeView :
	public IMatrixLayer
{
protected:
	point cameraPos;
	point cameraOrientation;
	float **mPos, **mOri;
public:

	void preProcessForward(){

		float pos[4], ori[4];
		cameraPos(pos);
		cameraOrientation(ori);
		for(int i=0; i<3; ++i){
			m1[i][3] = pos[i];
			m2[i][3] = ori[i];
		}
		Mul(mPos, mOri, matrix);
		

	}
		this->preProcessBackward();
	EyeView(point _cameraPos, point _cameraOrientation): 
						cameraPos(_cameraPos), 
						cameraOrientation(_cameraOrietation);{
		mPos = matrixINI<4>();
		mOri = matrixINI<4>();
	
		for(int i=0; i<4; ++i){
			mPos[i][i]=1.f;
			mOri[i][i]=1.f;	
		}
	}

	  void setCameraOrientation(point orientation){
		  cameraOrientation = orientation;
	  }

	  void setCameraPosition(point pos){
		  cameraPosition = pos;
	  }



	virtual ~EyeView(void)
	{
		matrixFREE(mPos);
		matrixFREE(mOri);
	}

private:
	EyeView(const EyeView&);
	EyeView& operator=(const EyeView&);
};
