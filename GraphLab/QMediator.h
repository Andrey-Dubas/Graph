#pragma once
#include "imediator.h"
#include "IControlContainer.h"
#include "IGraphContainer.h"
#include "QGraphContainer.h"
#include <QGraphicsScene>
#include <QGraphicsView>


class IMediator;
class QMediator :
	public IMediator
{
	Q_OBJECT
public:
	
public:

	virtual void graphEvent();

	static IMediator* mediator;

	static void init(QGraphContainer *gr, QControlContainer *ctrl, QWidget* view){
		mediator = new QMediator(gr, ctrl, view);
	}
	static IMediator* getInstance(){return mediator;}
	//void controlEvent()=0;
public:

	virtual ~QMediator(void)
	{
		delete graph;
		delete control;
	}

	/*virtual void graphEvent(){
		ObjectDescriptor desc = this->graph->getFullDescriptor();
		this->control->setDescriptor(&desc);
	}
	virtual void controlEvent(){}
*/
	QMediator(QGraphContainer *gr, QControlContainer *ctrl, QWidget* view):IMediator(gr, ctrl){
		QObject::connect(gr, SIGNAL(graphChange()), this, SLOT(graphInvoke()));
		//QObject::connect(gr, SIGNAL(onceRepaint()), this, SLOT(staticGraphInvoke()));
		
		ObjectDescriptor desc = this->graph->getFullDescriptor();
		this->control->setDescriptor(&desc);
		graph->drawPrepare();
	}
private:
	QMediator(const QMediator&);
	QMediator operator=(const QMediator&);
public slots:
	void graphInvoke(){
		graphEvent();
	}
	void staticGraphInvoke(){ // without n-times repainting
		graph->drawPrepare();
	}
};


