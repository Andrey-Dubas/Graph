#include "GraphicLib.h"
#include <list>
#include "CordContainer.h"
#include <math.h>
#include "IGrapgEntity.h"
#include "EdgeInfo.h"

#ifndef RAY_ALHORYTHM
#define RAY_ALHORYTHM

class IGrapgEntity;
typedef std::list<IGraphEntity*> ElementContainer;



void getEdges(EdgeInfo** edges, int width, int height, EdgeInfo** validateEdges, int& count, int dWidth, int dHeight);

void rayAlhorythm(ElementContainer objects, int width, int height, EdgeInfo** validateEdges, int& count, int dWidth, int dHeight);

void getContainedCircle(point** pArray, int rows, int cols, point& center, int& radius);

bool getPointedFace(int x, int y, EdgeInfo& info, point** cords, int rows, int cols);

#endif