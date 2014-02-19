#include "RayAngorythm.h"
#include "IGrapgEntity.h"
#include "EdgeInfo.h"
#include "GraphicLab.h"

void getEdges(EdgeInfo** edges, int width, int height, EdgeInfo** validateEdges, int& count, int dWidth, int dHeight){
	std::list<EdgeInfo> lst;
	std::list<EdgeInfo>::iterator it;

	EdgeInfo* arr = new EdgeInfo[10000];
	count=0;
	for(int i=0; i<height; i+=dHeight){
		for(int j=0; j<width; j+=dWidth){
			if(edges[i][j].pArray!=NULL){
				bool isContained=false;
				for(int k=0; k<count; ++k){
					if(arr[k].pArray==edges[i][j].pArray && arr[k].x==edges[i][j].x && arr[k].y==edges[i][j].y && edges[i][j].orientation == arr[k].orientation){
						isContained = true;
						break;
					}
				}
				if(isContained==false){
					arr[count] = edges[i][j];
					count++;
				}
			}
		}
	}

	*validateEdges = new EdgeInfo[count];
	memcpy(*validateEdges, arr, count*sizeof(EdgeInfo));
	delete [] arr;
}

void defineVisibleEdges(EdgeInfo** field, int width, int height, CordContainer& objCords, point center, int radius, int dWidth, int dHeight){
	int dH, dHSquare;
	EdgeInfo p;
	char str[5];
	int xRadius;
	int maxY = center.y+radius<height?center.y+radius:height;
	int minY = (center.y-radius)>0?(center.y-radius):0;
	
	int maxX, minX;
	for(int i= minY; i<maxY; i+=dHeight){
		dH = (i-center.y);
		xRadius = sqrt(float(radius*radius-dH*dH));

		maxX = center.x+xRadius>width?width:center.x+xRadius;
		minX = center.x-xRadius<0?0 : center.x-xRadius;


		for(int j=minX; j<maxX; j+=dWidth){
			if(getPointedFace(i, j, p, objCords.Cords, objCords.rows, objCords.cols)==true){
				if(field[i][j].pArray==NULL){
					field[i][j] = p;
				}
				else if(p.pArray[p.y][p.x].z < field[i][j].pArray[field[i][j].x][field[i][j].y].z){
					field[i][j] = p;   // if the curent finded edge is closer to observer
				}
			}
		}

		OutputDebugStringA(itoa(i, str, 10));
	}
}


void rayAlhorythm(ElementContainer objects, int width, int height, EdgeInfo** validateEdges, int& count, int dWidth, int dHeight){
	ElementContainer::iterator it;
	EdgeInfo** edges = new EdgeInfo*[height];
	for(int i=0; i<height; ++i){
		edges[i] = new EdgeInfo[width];
	}
	int elemsAmount = objects.size();
	point* centers = new point[elemsAmount];
	int* radiuses = new int[elemsAmount];


	CordContainer* cords;
	it = objects.begin();
	for(int i=0; i<elemsAmount; ++i){
		cords = (*it)->convertedPos;
		getContainedCircle(cords->Cords, cords->rows, cords->cols, centers[i], radiuses[i]);
		defineVisibleEdges(edges, width, height, *cords, centers[i], radiuses[i], dWidth, dHeight);
		it++;
	}

	getEdges(edges, width, height, validateEdges, count, dWidth, dHeight);


	delete[] centers;
	delete[] radiuses;
	for(int i=0; i<height; ++i){
		delete [] edges[i];
	}
	delete [] edges;

}

void getContainedCircle(point** pArray, int rows, int cols, point& center, int& radius){ // determine the sphere containing object
	LONGLONG radX=0;
	LONGLONG radY=0;

	float maxX = pArray[0][0].x, maxY = pArray[0][0].y, minX = pArray[0][0].x, minY = pArray[0][0].y;
	
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			radX+=pArray[i][j].x;
			radY+=pArray[i][j].y;
			
			if(pArray[i][j].x>maxX) maxX = pArray[i][j].x;
			if(pArray[i][j].y>maxY) maxY = pArray[i][j].y;

			if(pArray[i][j].x<minX) minX = pArray[i][j].x;
			if(pArray[i][j].y<minY) minY = pArray[i][j].y;
		}
	}

	center.x = radX / (rows*cols);  // determine the center of sphere
	center.y = radY / (rows*cols);

	radius = maxX-center.x + maxY-center.y;
	float temp = center.x-minX + center.y-minY;
	if(temp>radius) radius = temp; // define the radius of sphere
	radius*=1.1;
}



bool getPointedFace(int x, int y, EdgeInfo& info, point** cords, int rows, int cols){
	const int MAX = 30;
	int pointedX[MAX], pointedY[MAX], cordZ[MAX];
	bool pointedOrientation[MAX];
	int count=0;
	for(int i=0; i<rows-1; ++i){
		for(int j=0; j<cols-1; ++j){
			if(count<MAX-4){
				bool isIn = isInTriangle(cords[i][j].x, cords[i][j].y, cords[i+1][j].x, cords[i+1][j].y,
							cords[i][j+1].x, cords[i][j+1].y, x, y);
				if(isIn==true){
					pointedX[count] = i;
					pointedY[count] = j;
					cordZ[count] = cords[i][j].z; 
					pointedOrientation[count] = true;
					count++;
					info.pArray = cords;
					info.height = rows;
					info.width = cols;
				}

				isIn = isInTriangle(cords[i+1][j+1].x, cords[i+1][j+1].y, cords[i+1][j].x, cords[i+1][j].y,
							cords[i][j+1].x, cords[i][j+1].y, x, y);
				if(isIn==true){
					pointedX[count] = i;
					pointedY[count] = j;
					cordZ[count] = cords[i][j].z; 
					pointedOrientation[count] = false;
					count++;
					info.pArray = cords;
					info.height = rows;
					info.width = cols;
				}
			}
		}
	}
	if (count==0) return false;

	assert(count<MAX);
	int tempX, tempY, tempZ, tempOri;
	for(int i=0; i<count; ++i){
		for(int j=0; j<count-1; ++j){
			if(cordZ[j]>cordZ[j+1]){
				tempOri = pointedOrientation[j];
				tempX = pointedX[j];
				tempY = pointedY[j];
				tempZ = cordZ[j];
				
				pointedOrientation[j] = pointedOrientation[j+1];
				pointedX[j] = pointedX[j+1];
				pointedY[j] = pointedY[j+1];
				cordZ[j] = cordZ[j+1];
				
				pointedOrientation[j+1] = tempOri;
				pointedX[j+1] = tempX;
				pointedY[j+1] = tempY;
				cordZ[j+1] = tempZ;
			}
		}
	}
	info.orientation = pointedOrientation[0];
	info.x = pointedX[0];
	info.y = pointedY[0];
	info.pArray = cords;
	info.height = rows;
	info.width = cols;

	return true;
}


void fillPoints(EdgeInfo& info, int width, int Height, point** cords, int rows, int cols){
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){

		}
	}
}