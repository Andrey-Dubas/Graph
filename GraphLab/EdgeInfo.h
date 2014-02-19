#ifndef EDGE_INFO_H
#define EDGE_INFO_H
struct EdgeInfo{
	point** pArray;
	int width, height;
	int x, y;
	bool orientation;
	EdgeInfo():pArray(NULL){}
};


struct ColorPixel{
	float intensity;
	union{
		int colors;
		UCHAR r, g, b;
	};
};

#endif