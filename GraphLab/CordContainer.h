#pragma once

#include "graphicLib.h"

class CordContainer
{
public:					// hiload class, so getting cords without getter
	point** Cords;
	size_t rows;
	size_t cols;
public:

	void convertCordInit(point**_cords, UINT _rows, UINT _cols){
		rows = _rows; cols = _cols;
		this->Cords = _cords;
	}

	void convertCordInit(const CordContainer& obj){ //used in copy constructor
		rows = obj.rows; cols = obj.cols;
		this->Cords = new point*[rows];
		for(int i=0; i<rows; ++i){
			Cords[i] = new point[cols];
			for(int j=0; j<cols; ++j){
				Cords[i][j] = obj.Cords[i][j];
			}
		}
	}


	CordContainer(const CordContainer& obj){
		convertCordInit(obj);
	}

	CordContainer operator=(const CordContainer& obj){
		convertCordInit(obj);
		return *this;
	}

	virtual void clone(CordContainer& obj){
		rows = obj.rows; cols = obj.cols;
		Cords= obj.Cords;
	}

	CordContainer(point** _cords, size_t _rows, size_t _cols){
		convertCordInit(_cords, _rows, _cols);
	}

	CordContainer(){
		Cords = NULL;
		rows=0; cols = 0;
	}

	CordContainer(UINT _rows, UINT _cols){
		rows=_rows; cols = _cols;
		this->Cords = new point*[rows];
		for(int i=0; i<rows; ++i){
			this->Cords[i] = new point[cols];
		}
	}


	virtual ~CordContainer(void){
		if(Cords!=NULL){
			for(int i=0; i<rows; ++i){ 
				delete [] Cords[i];
			}
			delete [] Cords;
		}
	}
};
