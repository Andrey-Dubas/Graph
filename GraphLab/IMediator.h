#pragma once
#include "QControlContainer.h"
#include "IGraphContainer.h"
#ifdef QT_GUI_LIB
	#include <QObject>
	#define QT_SLOT   slots
	#define QT_OBJECT_INHERITANCE :public QObject
	#define QT_SIGN Q_OBJECT
#endif
#ifndef QT_GUI_LIB
	#define QT_SLOT
	#define QT_OBJECT_INHERITANCE
	#define QT_SIGN
#endif

class IMediator: public QObject{
public:
	Q_OBJECT
protected:
	IGraphContainer* graph;
	QControlContainer* control;
	
/*public QT_SLOT:
	
	void controlEvent()=0;*/
public:
	virtual void graphEvent()=0;
	IMediator(IGraphContainer* _graph, QControlContainer* _control):graph(_graph), control(_control){}
	
	virtual ~IMediator(void)
	{
	}
private:
	IMediator(void){}
	IMediator(const IMediator& obj){}
	const IMediator& operator= (const IMediator& obj){}
};
