#include "ISurface.h"
#include "LayerGenerator.h"


void ISurface::recalculateInitialData(){
	this->origPos = CordContainer(amountU, amountV);
	float U=0, V=0, dU = 1./(float)(amountU-2), dV = 1./(float)(amountV-2);

	for(int i=0; i<amountU; ++i){
		
		for(int j=0; j<amountV; ++j){
			origPos.Cords[i][j] = function(U, V);
			V += dV;
		}
		U+=dU;
		V=0;
	}
}


ISurface::~ISurface(void)
{
}

bool ISurface::isPointIn(float x, float y){
	point A, B, C;
	int rowPos, colPos; //get a position of the start point of edge's triangle 
	bool isPointed = getPointedFace(point(x, y, 0), A, B, C);
	if(isPointed==true){
		for(int i=0; i<this->convertedPos->rows; ++i){			//
			for(int j=0; j<this->convertedPos->cols; ++j){		// searching the number of point
				if(A==convertedPos->Cords[i][j]){				//
					rowPos=i; colPos=j;							//
				}
			}
		}
		if(rowPos==convertedPos->rows-1 || colPos==convertedPos->cols-1){
			assert(rowPos!=convertedPos->rows-1);
		}
		else{
			A = convertedPos->Cords[rowPos][colPos];	//get originalCords
			B = convertedPos->Cords[rowPos+1][colPos];
			C = convertedPos->Cords[rowPos][colPos+1];
			
			point center = getTriangleCenter(A, B, C);
			vector vec = normalToSurface(A, B, C);

			normalC = center;
			this->normalOrientation = vec;
			vec= vec/hypotenuse(vec);
			vec*=200;


			LayerContainer l;
			/*for(LayerContainer::iterator it = LayerStack.begin(); it!=LayerStack.end(); it++){
				l.push_front((*it)->clone());
			}*/
			//uncomment when reverseProcess will be ok

			this->descriptionElements.push_front(new Line(center, center+vec, l));
			return true;
		}
		return false;
	}

	/*if(normal!=NULL){
		delete normal;
		normal = NULL;
	}*/

	return false;
}


/*ElementContainer ISurface::getDescriptionElements(){
	ElementContainer container;
	if(normal!=NULL){
		container.push_back(normal);
	}
	return container;
}*/
