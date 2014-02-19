#pragma once
#include <QGraphicsView>
#include <QWidget>
#include <QPaintEvent>

class MyQGraphicsView :
	public QWidget
{
	Q_OBJECT
public:
	MyQGraphicsView(void);
	MyQGraphicsView(QWidget* w=0):QWidget(w){

	}
	virtual ~MyQGraphicsView(void);
protected:
	void paintEvent(QPaintEvent* pEvent);
	virtual void mouseMoveEvent ( QMouseEvent *) override;
	virtual void mousePressEvent ( QMouseEvent *) override;
signals:
	void mouseMoveE( QPointF mouseEvent );
	void mousePressE( QPointF mouseEvent );
};
