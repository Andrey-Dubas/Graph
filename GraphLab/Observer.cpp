#include "Observer.h"
#include "graphicLib.h"
Observer::Observer(point pos, point ori):position(pos), orientation(ori){
	registerClassDescriptor();
	m1 = matrixINI<4>();
	m2 = matrixINI<4>();
	for(int i=0; i<4; ++i){
		m1[i][i] = 1;
		m2[i][i] = 1;
	}
}

void Observer::preProcessForward(){
	float v1[4];
	this->position(v1);
	//this->orientation(v2);

	for(int i=0; i<3; i++){
		m1[i][3] = v1[i];
	}
	Evclid::rotateMatrix(m2, orientation);

	Mul(m1, m2, this->matrix);
}

void Observer::setPosition(point pos){ this->position = pos;}
void Observer::setOrientation(point ori){this->orientation = ori;}


Observer::~Observer(void)
{
	matrixFREE<4>(m1);
	matrixFREE<4>(m2);
}
