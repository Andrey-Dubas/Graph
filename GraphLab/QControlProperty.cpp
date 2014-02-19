#include "QControlProperty.h"
#include <QObject>
#include <QLineEdit>
#include <QString>
#include <QValidator>
#include "NumProperty.h"
#include "PointProperty.h"

#include "QControlContainer.h"
#include "QMediator.h"

QControlProperty::QControlProperty(IGraphProperty* prop):IControlProperty(prop){
}

QControlProperty::~QControlProperty(void)
{
}


QLabel* QControlProperty::getControls(std::vector<QLabel*>& descriptors, std::vector<QLineEdit*>& editors){
	descriptors.clear();
	editors.clear();
	ValueIntProperty* intProp;
	ValueFloatProperty* floatProp;
	ValuePointProperty* pointProp;

	char str[40];
	if(intProp = dynamic_cast<ValueIntProperty*>(prop)){
		getControls(descriptors, editors, *intProp);
	}
	if(floatProp = dynamic_cast<ValueFloatProperty*>(prop)){
		getControls(descriptors, editors, *floatProp);
	}

	if(pointProp = dynamic_cast<ValuePointProperty*>(prop)){
		getControls(descriptors, editors, *pointProp);
	}
	editorVector = editors;

	WideCharToMultiByte(CP_ACP, 0   , prop->getName(), 40               , str, 40, NULL, NULL); 
	return new QLabel(str);
}


QLabel* QControlProperty::getControls(std::vector<QLabel*>& descriptors, std::vector<QLineEdit*>& editors, ValueFloatProperty prop){
	char str[10];
	QLineEdit* val = new QLineEdit(QString());
	val->setText(QString(_gcvt(prop.getValue(), 4, str)));
	val->setValidator(new QDoubleValidator(10000, -10000, 4, NULL/*intProp->getMax(), intProp->getMin()*/));
	editors.push_back(val);
	QObject::connect(editors[0], SIGNAL(selectionChanged()), this, SLOT(setSingleValue()));
	return NULL;
}
QLabel* QControlProperty::getControls(std::vector<QLabel*>& descriptors, std::vector<QLineEdit*>& editors, ValueIntProperty prop){
	char str[10];
	QLineEdit* val = new QLineEdit(QString(itoa(prop.getValue(), str, 10)));
	val->setValidator(new QIntValidator(-100000, 100000, NULL/*intProp->getMax(), intProp->getMin()*/));
	editors.push_back(val);
	QObject::connect(editors[0], SIGNAL(selectionChanged()), this, SLOT(setSingleValue()));
	return NULL;
}
QLabel* QControlProperty::getControls(std::vector<QLabel*>& descriptors, std::vector<QLineEdit*>& editors, ValuePointProperty prop){
	char str[40];
	QLineEdit* val1 = new QLineEdit(); val1->setText(QString(_gcvt(prop.getValue().x, 4, str)));
	QLineEdit* val2 = new QLineEdit(); val2->setText(QString(_gcvt(prop.getValue().y, 4, str)));
	QLineEdit* val3 = new QLineEdit(); val3->setText(QString(_gcvt(prop.getValue().z, 4, str)));
	
	editors.push_back(val1);
	editors.push_back(val2);
	editors.push_back(val3);

	for(int i=0; i<editors.size(); ++i){
		editors[i]->setValidator(new QDoubleValidator(double(-10000), double(0x7FFFFFFF), 4, NULL));
		QObject::connect(editors[i], SIGNAL(selectionChanged()), this, SLOT(setPoint1()));
	}

	descriptors.push_back(new QLabel("X:"));
	descriptors.push_back(new QLabel("Y:"));
	descriptors.push_back(new QLabel("Z:"));
	return NULL;
}


void QControlProperty::setSingleValue(){
	ValueFloatProperty* numProp = dynamic_cast<ValueFloatProperty*>(prop);
	if((editorVector.size()!=1)||(numProp==NULL)){
		///exception
		//return;
	}
	else{
		float p;
		p = editorVector[0]->text().toFloat();
		numProp->setValue(p);
		numProp->setProperty();
	}
	ValueIntProperty* numIntProp = dynamic_cast<ValueIntProperty*>(prop);
	if((editorVector.size()!=1)||(numIntProp==NULL)){
		///exception
		//return;
	}
	else{
		int p1;
		p1 = editorVector[0]->text().toInt();
		numIntProp->setValue(p1);
		numIntProp->setProperty();
	}

		
		
		//QControlContainer::getInstance()->
		QMediator::getInstance()->graphEvent();
		QControlContainer::getInstance()->controlContextChanged();
	
}

void QControlProperty::setPoint(){
	ValuePointProperty* pointProp = dynamic_cast<ValuePointProperty*>(prop);
	if((editorVector.size()!=3)||(pointProp==NULL)){
		///exception
	}
	else{
		point p;
		p.x = editorVector[0]->text().toFloat();
		p.y = editorVector[1]->text().toFloat();
		p.z = editorVector[2]->text().toFloat();
		pointProp->setValue(p);
		pointProp->setProperty();
		QControlContainer::getInstance()->controlContextChanged();
	}
}


void QControlProperty::setPoint1(){

	ValuePointProperty* pointProp = dynamic_cast<ValuePointProperty*>(prop);
	if((editorVector.size()!=3)||(pointProp==NULL)){
		///exception
	}
	else{
		point p;
		p.x = editorVector[0]->text().toFloat();
		p.y = editorVector[1]->text().toFloat();
		p.z = editorVector[2]->text().toFloat();
		pointProp->setValue(p);
		pointProp->setProperty();
		QControlContainer::getInstance()->controlContextChanged();
	}
}