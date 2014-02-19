#include "QGraphContainer.h"
#include "GraphContainer.h"
#include "Line.h"
#include "IGraphLayer.h"
#include "QGraphicsModel.h"
#include <QPoint>
#include <QGraphicsTextItem>
#include <QString>
#include "Conus.h"
#include "RationalCurve.h"
#include "QPainter.h"
#include "MyQGraphicsView.h"
#include "RayAlhorythm.h"

QGraphContainer* QGraphContainer::instance = NULL;

QGraphContainer* QGraphContainer::getInstance(){return instance;}

void QGraphContainer::init(MyQGraphicsView* ctrl, QPaintDevice* dev){
	if(instance==NULL)instance = new QGraphContainer(ctrl, dev);
}

QGraphContainer::QGraphContainer(MyQGraphicsView* ctrl, QPaintDevice* _dev):GraphContainer<QGraphicsModel>(ctrl), dev(ctrl), painter(_dev)
{
	this->dWidth = 1;
	this->dHeight= 1;

	edgesToDraw = new EdgeInfo[0];// for preventing if
	for(int i=0; i<3; ++i){
		selectedEdgeDescriptor[i] = 0;
	}
	
	connect(this, SIGNAL(callRepaint()), ctrl, SLOT(repaint()));
	connect(ctrl, SIGNAL(mouseMoveE(QPointF)), this, SLOT(mouseMove(QPointF)));
	connect(ctrl, SIGNAL(mousePressE(QPointF)), this, SLOT(mousePress(QPointF)));
	currentTick=0;
	QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(invokeDraw()));
	point points[] = {point (-50, 0, 0), point (-100, 50, 0), point (-150, 100, 0), point(-50, 130, 0), point(-250, 150, 100), point(-50, 180, 100), point(-20, 200, 0)};
	float mass[] = {1, 1, 3, 1, 2, 2, 1};

	devWidth = _dev->width();
	devHeight = _dev->height();
	colorField = new ColorPixel*[devHeight];
	for(int i=0; i<devHeight; ++i){
		colorField[i] = new ColorPixel[devWidth];
		for(int j=0; j<devWidth; ++j){
			colorField[i][j].colors = 0;
			colorField[i][j].intensity = 0;
		}
	}

	//this->collection.push_back(new RationalCurve(points, mass, 7, 100, 20, 20));
	this->collection.push_back(new Conus(250, 150, 20, 20));
	
	
}

QGraphContainer::~QGraphContainer(void)
{
	delete [] edgesToDraw;

	for(int i=0; i<devHeight; ++i){
		delete [] colorField[i];
	}
	delete [] colorField;
	//for(int i=0; i<texts.size(); ++i){
		//delete texts[i];
	//}
	//this->collection.clear();
}


void QGraphContainer::updateLayerInfo(){
	std::list<IGraphLayer*> singleLayer = LayerGenerator::getInstance()->getSingletonLayers();
	this->descriptor->clearChildren();

	for(std::list<IGraphLayer*>::iterator it = singleLayer.begin(); it!=singleLayer.end(); ++it){
		this->descriptor->addChildren(new ObjectDescriptor((*it)->getDescriptor()));
	}
	for(ElementContainer::iterator it = collection.begin(); it!=collection.end(); it++){
		(*it)->updateLayerInfo();
	}
}

void QGraphContainer::clear(){
	//this->paintControl->clear();
}

void QGraphContainer::draw(){
	painter.begin(dev);
	painter.eraseRect(0, 0, 1000, 700);
	for(int i=0; i<1000; ++i){
		for(int j=0; j<700; ++j){
			if(colorField[j][i].intensity>0){
				painter.setPen(QColor(0, 255, (255*(1-this->colorField[j][i].intensity))));
				painter.drawPoint(i, j);
			}
		}
	}

	
	painter.setPen(QColor(0, 0, 0));
	ElementContainer::iterator it;
	ElementContainer::iterator it1;
	ElementContainer graphDescriptions;
	/*for(it=collection.begin(); it!=collection.end(); ++it){
		drawEntity((*it)->getPointToDraw(), edgesToDraw, this->edgesCount);

		graphDescriptions = (*it)->getDescriptionElements();
		it1 = graphDescriptions.begin();
		for(; it1!=graphDescriptions.end(); it1++){
			drawEntity((*it1)->getPointToDraw());
		}
	}*/
	painter.end();
}

void QGraphContainer::drawPrepare(){

	for(int i=0; i<1000; ++i){
		for(int j=0; j<700; ++j){
				this->colorField[j][i].intensity=0;
		}
	}

	DWORD startTime, outerStartTime = GetTickCount();
	char str[40];
	ElementContainer::iterator it;
	ElementContainer::iterator it1;

	float progress = ((float)++currentTick + 0.01)/(float)maxTick;
	if(currentTick==maxTick){
		for(int i=0; i<3; i++){
			delete this->selectedEdgeDescriptor[i];
			selectedEdgeDescriptor[i]=NULL;
		}
		for(it=collection.begin(); it!=collection.end(); ++it){
			(*it)->clearDescriptionElements();
		}
		currentTick = 0;
		timer.stop();
	}

	CordContainer* cords;
	
	if(selectedEdgeDescriptor[0]!=NULL){
		this->edgeInfoOut(*selectedEdgeDescriptor[0], 
				*selectedEdgeDescriptor[1], 
				*selectedEdgeDescriptor[2]);
	}
	
	ElementContainer graphDescriptions;
	
	for(it=collection.begin(); it!=collection.end(); ++it){
		(*it)->processUpdate(progress);
		(*it)->process();
		graphDescriptions = (*it)->getDescriptionElements();
		for(it1 = graphDescriptions.begin(); it1!=graphDescriptions.end(); it1++){
			(*it1)->processUpdate(progress);
			(*it1)->process();
		}
	}

	delete [] edgesToDraw;
	//rayAlhorythm(collection, 700, 1000, &edgesToDraw, edgesCount, dWidth, dHeight);
	edgeNormalCreate((*collection.begin())->convertedPos, edgesToDraw, edgesCount, this->colorField, 700, 1000, point(0, 0, 1), 70);

}

ObjectDescriptor QGraphContainer::getFullDescriptor(){
	updateLayerInfo();
	ObjectDescriptor desc = this->getDescriptor();

	int size = this->selectedCollection.size();
	std::list<IGraphEntity*>::const_iterator it;
	for(it=selectedCollection.begin(); it!=selectedCollection.end(); ++it){
		desc.addChildren(new ObjectDescriptor((*it)->getDescriptor()));
	}
	return desc;
}


void QGraphContainer::mouseMove(QPointF p){
	/*int size = this->collection.size();
	point A, B, C;
	ElementContainer::iterator it;

	char str[40];
	OutputDebugStringA(itoa(p.x(), str, 10));
	OutputDebugStringA(" : ");
	OutputDebugStringA(itoa(p.y(), str, 10));
	OutputDebugStringA("\n");

	for(it=collection.begin(); it!=collection.end(); ++it){
		if((*it)->pointIn(p.x(), p.y())==true){
			this->selectedCollection.push_back(*it);
			if((*it)->getPointedFace(point(p.x(), p.y(), 0), A, B, C)==true){
				//edgeInfoOut(A, B, C);
				
			}
			break;
		}
	}*/
}

void QGraphContainer::edgeInfoOut(point A, point B, point C){
	point arr[3];
	arr[0] = outOfTriangle(A, B, C)*80+A;
	arr[1] = outOfTriangle(B, A, C)*80+B;
	arr[2] = outOfTriangle(C, B, A)*80+C;
	QGraphicsTextItem* localTexts[3];
	
	char str[40];
	for(int i=0; i<3; i++){
		sprintf(str, "[%8.2f:%8.2f]", arr[i].x, arr[i].y);
		//localTexts[i] = paintControl->addText(QString(str));
		//localTexts[i]->setPos(arr[i].x, arr[i].y);
	}
}


void QGraphContainer::mousePress(QPointF p){
	int size = this->collection.size();
	ElementContainer::iterator it;
	this->selectedCollection.clear();
	point nativePoint = point(p.x(), p.y(), 0);
	point A, B, C;
	for(it=collection.begin(); it!=collection.end(); ++it){
		if((*it)->pointIn(nativePoint.x, nativePoint.y)==true){
			this->selectedCollection.push_back((*it));
			OutputDebugString(L"mousePress");
			
			if(selectedEdgeDescriptor[0]==NULL){
				for(int i=0; i<3; ++i){
					selectedEdgeDescriptor[i] = new point;
				}
			}
			(*it)->getPointedFace(nativePoint, *selectedEdgeDescriptor[0], 
				*selectedEdgeDescriptor[1], *selectedEdgeDescriptor[2]);
			
			emit graphChange();

			break;
		}
	}
	

}


void QGraphContainer::drawEntity(CordContainer* cords){
	int x1, x2, x3, x4, y1, y2, y3, y4;
	int rows = cords->rows, cols = cords->cols;
	point** CordArray = cords->Cords;
	
	
	
	//painter.
	for(int i=0; i<rows-1; ++i){
		for(int j=0; j<cols-1; ++j){
			x1 = CordArray[i][j].x;
			x2 = CordArray[i][j+1].x;
			x3 = CordArray[i+1][j].x;
			x4 = CordArray[i+1][j+1].x;

			y1 = CordArray[i][j].y;
			y2 = CordArray[i][j+1].y;
			y3 = CordArray[i+1][j].y;
			y4 = CordArray[i+1][j+1].y;
			
			/*this->paintControl->addLine(x1, y1, x2, y2);
			this->paintControl->addLine(x4, y4, x1, y1);
			this->paintControl->addLine(x1, y1, x3, y3);*/
			painter.drawLine(x1, y1, x2, y2);
			painter.drawLine(x4, y4, x1, y1);
			painter.drawLine(x1, y1, x3, y3);

		}
	}
	for(int i=0; i<rows-1; ++i){
		x1 = CordArray[i][cols-1].x;
		x2 = CordArray[i+1][cols-1].x;

		y1 = CordArray[i][cols-1].y;
		y2 = CordArray[i+1][cols-1].y;

		painter.drawLine(x1, y1, x2, y2);
		//this->paintControl->addLine(x1, y1, x2, y2);
	}
	for(int i=0; i<cols-1; ++i){
		x1 = CordArray[rows-1][i].x;
		x2 = CordArray[rows-1][i+1].x;

		y1 = CordArray[rows-1][i].y;
		y2 = CordArray[rows-1][i+1].y;

		painter.drawLine(x1, y1, x2, y2);
		//this->paintControl->addLine(x1, y1, x2, y2);
	}
}

void QGraphContainer::drawEntity(CordContainer* cords, EdgeInfo* edges, int count){
	int x1, x2, x3, x4, y1, y2, y3, y4;
	int rows = cords->rows, cols = cords->cols;
	point** CordArray = cords->Cords;

	point p1, p2, p3;
	for(int i=0; i<count; ++i){
		if(edges[i].pArray==cords->Cords){
			if(edges[i].orientation){
				p1 = CordArray[edges[i].x]  [edges[i].y];
				p2 = CordArray[edges[i].x+1][edges[i].y];
				p3 = CordArray[edges[i].x]  [edges[i].y+1];
			}
			else{
				p1 = CordArray[edges[i].x+1][edges[i].y+1];
				p2 = CordArray[edges[i].x]  [edges[i].y+1];
				p3 = CordArray[edges[i].x+1][edges[i].y];
			}
			x1 = p1.x;
			x2 = p2.x;
			x3 = p3.x;
			//x4 = p4.x;

			y1 = p1.y;
			y2 = p2.y;
			y3 = p3.y;
			//y4 = CordArray[i+1][j+1].y;
			
			painter.drawLine(x1, y1, x2, y2);
			painter.drawLine(x2, y2, x3, y3);
			painter.drawLine(x3, y3, x1, y1);
		}

	}
}