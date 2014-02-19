#include "GraphicLib.h"
#include "CordContainer.h"
#include "RayAlhorythm.h"
#include <list>
#include "FongMethod.h"
#include "EdgeInfo.h"
#include "GraphicLib.h"

vector getNormaltoEdge(EdgeInfo edge, int maxX, int maxY){
	int x1, x2, x3;
	int y1, y2, y3;
	
	if(edge.x<1){
		edge.x = 1;
	}
	if(edge.x>maxX-2){
		edge.x = maxX-2;
	}

	if(edge.y<1){
		edge.y = 1;
	}
	if(edge.y>maxY-2){
		edge.y = maxY-2;
	}

	if(edge.orientation==true){
		x1 = edge.x;
		x2 = edge.x+1;
		x3 = edge.x;

		y1 = edge.y;
		y2 = edge.y;
		y3 = edge.y+1;
	}
	else{
		x1 = edge.x;
		x2 = edge.x+1;
		x3 = edge.x+1;

		y1 = edge.y+1;
		y2 = edge.y;
		y3 = edge.y+1;
	}

	return normalToSurface(edge.pArray[x1][y1], edge.pArray[x2][y2], edge.pArray[x3][y3]); // нормаль к грани 
	


}

void GetVectorsForEdge(EdgeInfo edge, vector& v1, vector& v2, vector& v3, int maxX, int maxY){ // Вычисляются нормали ко всем полигонам.
	int x[3][6], y[3][6];
	if(edge.orientation==true){
		x[0][0] = edge.x;
		y[0][0] = edge.y;
		
		x[1][0] = edge.x+1;
		y[1][0] = edge.y;

		x[2][0] = edge.x;
		y[2][0] = edge.y+1;
	}
	else{
		x[0][0] = edge.x;
		y[0][0] = edge.y+1;
		
		x[1][0] = edge.x+1;
		y[1][0] = edge.y;

		x[2][0] = edge.x+1;
		y[2][0] = edge.y+1;
	}

	for(int i=0; i<3; i++){
		for(int j=1; j<4; ++j){
			x[i][j] = x[i][0];
			y[i][j] = y[i][0];
		}

		x[i][1] = x[i][0]-1;
		y[i][2] = y[i][0]-1;
		y[i][3] = y[i][0]-1;
	}


	EdgeInfo edges[3][6];
	for(int i=0; i<3; ++i){
		for(int j=0; j<4; ++j){
			edges[i][j] = edge;
			edges[i][j].x = x[i][j];
			edges[i][j].y = y[i][j];
		}
	}

	v1=point(0, 0, 0);
	v2=point(0, 0, 0);
	v3=point(0, 0, 0);

	for(int j=0; j<1; ++j){
		v1 = v1+getNormalToEdge(edges[0][j], maxX, maxY);
		v2 = v2+getNormalToEdge(edges[1][j], maxX, maxY);
		v3 = v3+getNormalToEdge(edges[2][j], maxX, maxY);
	}

}


void interPolation(EdgeInfo edge, float v1, float v2, float v3, ColorPixel** field, int height, int width, float intensity){
	// Каждый многоугольник закрашивается путем линейной интерполяции значений интенсивностей в вершинах сначала вдоль каждого ребра, а затем и между ребрами вдоль каждой сканирующей строки 
	float px1, px2, pCur;
	float vx1, vx2, vCur;
	float u, v;
	
	float curWidth;
	float buf;
	point p1, p2, p3;
	if(edge.orientation==true){
		p1 = edge.pArray[edge.x][edge.y];
		p2 = edge.pArray[edge.x+1][edge.y];
		p3 = edge.pArray[edge.x][edge.y+1];
	}//
	else{
		p1 = edge.pArray[edge.x][edge.y+1];
		p2 = edge.pArray[edge.x+1][edge.y];
		p3 = edge.pArray[edge.x+1][edge.y+1];
	}
	float maxX = max(hypotenuse(p1, p2), hypotenuse(p1, p3));
	float intensity1=0;
	float k=1.0;
	float byf=0;
	char str[10];


	for(int i=0; i<maxX; ++i){
		u = i/(float)(maxX);

		px1 = p1+(p2-p1)*u;   px2 = p1+(p3-p1)*u;
		vx1 = v1+(v2-v1)*u*k; vx2 = v1+(v3-v1)*u*k;
		curWidth = hypotenuse(px1, px2);
		for(int j=0; j<curWidth; ++j){
			v = j/(float)(curWidth);
			pCur = px1*v  + px2*(1-v);
			buf = vx1*v*k + vx2*(1-v*k);
			buf = buf/hypotenuse(buf);

			if(pCur.x>0 && pCur.y>0 && pCur.x<width && pCur.y<height){
				
				field[(int)pCur.y][(int)pCur.x].intensity = byf;//intensity;
				// вычисление интенсивности на основании перемножения нормали к грани и перпендикулярно к источнику освещения 
			}
		}
	}
}


void EdgeNormalCreate(CordContainer* cords, EdgeInfo* edgesToDraw, int countEdges, ColorPixel** field, int height, int width, point source, float intensity){// create normals to edges
	float v1, v2, v3;
	for(int k=0; k<countEdges; ++k){
		getIntensitiesForEdge(edgesToDraw[k], v1, v2, v3, cords->rows, cords->cols);
		interpolation(edgesToDraw[k], v1, v2, v3, field, height, width, scalarMul(buf, source)/(hypotenuse(buf)*hypotenuse(source)));
                                                                        // вычисление интенсивности 
	}
}