#include "GraphicLib.h"
#include "CordContainer.h"
#include "RayAlhorythm.h"
#include <list>
#include "EdgeInfo.h"

vector getNormalToEdge(EdgeInfo edge, int maxX, int maxY);

void getVectorsForEdge(EdgeInfo edge, vector& v1, vector& v2, vector& v3, int maxX, int maxY);


void interpolation(EdgeInfo edge, vector v1, vector v2, vector v3, ColorPixel** field, int height, int width, point source, float intensity);


void edgeNormalCreate(CordContainer* cords, EdgeInfo* edgesToDraw, int countEdges, ColorPixel** field, int height, int width, point source, float intensity);





