#include "graphiclab.h"
#include "QGraphContainer.h"
#include "QControlContainer.h"

#include "QControlContainer.h"
#include "QMediator.h"

#include "QControlProperty.h"
#include "PointProperty.h"
#include "NumProperty.h"
#include <QPushButton>
#include <QLineEdit>
#include <QApplication>
#include "QGraphicsModel.h"
#include "MyQGraphicsView.h"
#include "QScrollArea.h"
#include "C:\Qt\4.6.4\src\qt3support\widgets/q3scrollview.h"
#include <QVBoxLayout>
//#include <QGraphicScene>
GraphicLab::GraphicLab(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	//

	ui.setupUi(this);

	
	QFrame* frame = new QFrame(this);
	QScrollArea* scr = new QScrollArea(frame);
	QFrame* frame1 = new QFrame(scr);
	scr->setGeometry(QRect(0, 20, 200, 700));
	scr->setWidget(frame1);
	frame->setGeometry(QRect(1020, 1020, 200, 700));
	//frame->setGeometry(QRect(1020, 20, 200, 700));
	frame->show();
	frame1->setGeometry(QRect(2000, 2000, 200, 2600));
	frame1->show();

	paintObj = new MyQGraphicsView(this);
	paintObj->setMouseTracking(true);
    paintObj->setObjectName(QString::fromUtf8("paintObj"));
    paintObj->setGeometry(QRect(20, 10, 1000, 750));
	paintObj->setVisible(true);
	paintObj->show();
	paintObj->setAutoFillBackground(true);

	QGraphContainer::init((MyQGraphicsView*)paintObj, this->paintObj);//* gc = new QGraphContainer(gsc);

	QControlContainer::init(frame1);//* ctrl = new QControlContainer(this->ui.frame);
	QMediator::init(QGraphContainer::getInstance(), QControlContainer::getInstance(), paintObj);
}

GraphicLab::~GraphicLab()
{
	//delete mediator;
}
