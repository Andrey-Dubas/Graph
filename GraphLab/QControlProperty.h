#pragma once
#include "icontrolproperty.h"
#include "NumProperty.h"
#include "PointProperty.h"
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <stack>
#include <QObject>
#include "ObjectDescriptor1.h"
#include <list>

class QControlProperty : public IControlProperty
{
	
protected:
	std::vector<QLineEdit*> editorVector;
public:
	QLabel* getControls(std::vector<QLabel*>& descriptors, std::vector<QLineEdit*>& editors);
	

	
	QControlProperty(IGraphProperty* prop);
	virtual ~QControlProperty(void);
protected:
	QLabel* getControls(std::vector<QLabel*>& descriptors, std::vector<QLineEdit*>& editors, ValueFloatProperty prop);
	QLabel* getControls(std::vector<QLabel*>& descriptors, std::vector<QLineEdit*>& editors, ValueIntProperty prop);
	QLabel* getControls(std::vector<QLabel*>& descriptors, std::vector<QLineEdit*>& editors, ValuePointProperty prop);
private:
	QControlProperty(void);
	QControlProperty operator=(const QControlProperty&){};
	
	Q_OBJECT
public slots:
	/*virtual */void setPoint();
	void setPoint1();
	/*virtual */void setSingleValue();
signals:
	void propertyChanged();
};
