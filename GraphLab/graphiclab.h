#ifndef GRAPHICLAB_H
#define GRAPHICLAB_H

#include <QtGui/QMainWindow>
#include "ui_graphiclab.h"
#include "QMediator.h"
#include <QLineEdit>
#include <QWidget>
class GraphicLab : public QMainWindow
{
	Q_OBJECT
protected:
	QWidget* paintObj;
public:
	GraphicLab(QWidget *parent = 0, Qt::WFlags flags = 0);
	~GraphicLab();

private:
	Ui::GraphicLab ui;
	QMediator* mediator;

	QLineEdit* edit;
	int count;
//public slots:
};

#endif // GRAPHICLAB_H
