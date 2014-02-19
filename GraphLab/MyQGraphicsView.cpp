#include "MyQGraphicsView.h"
#include "QGraphContainer.h"
#include <QPaintEvent>
#include <QMouseEvent> 
MyQGraphicsView::MyQGraphicsView(void)
{
}

MyQGraphicsView::~MyQGraphicsView(void)
{
}

void MyQGraphicsView::mouseMoveEvent ( QMouseEvent * mouseEvent ){
	emit mouseMoveE(mouseEvent->posF());
}
void MyQGraphicsView::mousePressEvent ( QMouseEvent * mouseEvent ){
	emit mousePressE(mouseEvent->posF());
}

void MyQGraphicsView::paintEvent(QPaintEvent* pEvent){
	QGraphContainer::getInstance()->draw();
}
