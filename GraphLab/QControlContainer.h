#pragma once
#include "icontrolcontainer.h"
#include <QFrame>
#include "ObjectDescriptor1.h"
#include "QControlProperty.h"
#include <vector>
#include <QWidget>
#include <QObject>

class QMediator;

class QControlContainer : public QObject,
	public IControlContainer
{
	Q_OBJECT

	static QControlContainer* instance;
public:
	void controlContextChanged();
	static QControlContainer* getInstance();
	static void init(QFrame* frame);
protected:
	int widgetWidth;
	int curPosition;
	QFrame* frame;
	std::vector<QWidget*> innerWidgets;
	std::vector<QControlProperty*> controlProperties;
public:
	/*virtual */void setDescriptor(ObjectDescriptor* desc);
	QControlContainer(QFrame* frame);
	~QControlContainer(void);
protected:
	void singleDescriptorVisualize(ObjectDescriptor* desc);
	void recursiveDescriptorVisualize(ObjectDescriptor* desc);
	void destroyInnerWidgets();
	void prepareToDestroyWidgets();
	
	//QControlContainer(const QControlContainer&);
private:
	QControlProperty& operator=(const QControlProperty &);
	QControlContainer(void);
};
