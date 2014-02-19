#pragma once
#include "graphcontainer.h"
#include <QGraphicsScene>
#include "CordContainer.h"
#include <QObject>
#include <QTimer>
#include "QGraphicsModel.h"
#include <QPainter>
#include "FongMethod.h"

class MyQGraphicsView;

struct EdgeInfo;

class QGraphContainer : public QObject, 
	public GraphContainer<QGraphicsModel>
{
protected:
	QPainter painter;
	MyQGraphicsView* dev;
	QTimer timer;
	static const int maxTick = 1;
	int currentTick;
	ColorPixel** colorField;
	int devWidth, devHeight;
	Q_OBJECT
public slots:
	void invokeDraw(){
		drawPrepare();
		emit callRepaint();
		
	}
public:
	static QGraphContainer* instance;
	static QGraphContainer* getInstance();
	static void init(MyQGraphicsView* ctrl, QPaintDevice* dev);
	virtual void clear();
	point* selectedEdgeDescriptor[3];
	EdgeInfo* edgesToDraw;
	int edgesCount;
	int dWidth, dHeight;
private:
	//point outOfTriangle(point outPoint, point l1, point l2);
			
public:
	virtual void pictureParamsChanged(){
		currentTick=0;
		timer.start(100);
	}



	virtual void draw();
	virtual void drawPrepare();
	void drawEntity(CordContainer* cords, EdgeInfo* edges, int count);
protected:
	void edgeInfoOut(point A, point B, point C);
	
	virtual void updateLayerInfo();

	virtual ObjectDescriptor getFullDescriptor();


	void drawEntity(CordContainer* cords);
public:

	QGraphContainer(MyQGraphicsView* ctrl, QPaintDevice* _dev);
	virtual ~QGraphContainer(void);
private:
	QGraphContainer(const QGraphContainer& obj);
	const QGraphContainer& operator=(const QGraphContainer& obj);
public slots:
	void mouseMove(QPointF p);
	void mousePress(QPointF p);
signals:
	void graphChange();
	void callRepaint();

};

