/*#pragma once
#include "igraphlayer.h"


class IGraphEntity;


const int undef = 0x80000000;
struct EdgeInfo{
	IGraphEntity* obj;
	int x, y;
	bool orientation;
	EdgeInfo():obj(NULL){
	}
};

inline bool operator==(const EdgeInfo& lhs, const EdgeInfo& rhs){
	return (lhs.x==rhs.x)&&(lhs.y==rhs.y)&&(lhs.orientation==rhs.orientation)&&(lhs.obj==rhs.obj);
}

class RayAngorythm :
	public IGraphLayer
{
protected:
	
	point center;
	float radius;

	EdgeInfo** currentPoints;// 2-dimentional array of point refs
	std::list<EdgeInfo> selectedPoints;
	int height, width;
public:
	PRIORITY(6);
	SINGLETON(TRUE);
	NOT_CLONNABLE;



	virtual void recalculateInitialData(){}
	void globalPointDefine(){
		EdgeInfo p;
		bool contained = false;
		std::list<EdgeInfo>::iterator it;
		for(int i=0; i<height; ++i){
			for(int j=0; j<width; ++j){
				if(currentPoints[i][j].obj!=NULL){
					contained = false;
					for(it = selectedPoints.begin(); it!=selectedPoints.end(); ++it){
						//memcpy(p, (*it), sizeof(point*)*3);
						//std::list<point*>::iterator it;
						if((*it) == currentPoints[i][j]){
							contained = true;
							break;
						}
					}
					if(!contained){
						selectedPoints.push_front(currentPoints[i][j]);
					}
				}
			}
		}
	}

	point* getPointToDraw(int edgeNum){
		return NULL;
	}
protected:
	virtual void process();
	bool getPointedFace(int x, int y, EdgeInfo& info);
	virtual void preProcessForward();
	virtual void preProcessBackward(){};//not supported here
	virtual void reverseProcess(void){}
	
public:
	RayAngorythm(int width, int height);
	~RayAngorythm(void);
};
*/