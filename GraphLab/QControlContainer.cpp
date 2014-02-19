#include "QControlContainer.h"
#include "ObjectDescriptor1.h"
#include "QControlProperty.h"
#include "IGraphProperty.h"

#include <QLabel>
#include <QRect>

#include "graphiclab.h"

#include "QMediator.h"

QControlContainer::QControlContainer(void){
}

QControlContainer::QControlContainer(QFrame* frame):widgetWidth(90){
	this->frame = frame;
}

QControlContainer::~QControlContainer(void){
	destroyInnerWidgets();
}


void QControlContainer::recursiveDescriptorVisualize(ObjectDescriptor* desc){
	ObjectDescriptor* curDesc = desc;
	std::vector<QWidget*> tempProperties;
	
	while(curDesc!=NULL){
		singleDescriptorVisualize(curDesc);
		curDesc = curDesc->lowerClassDescriptor;
	}		// get ancestors' descriptors
	
	std::vector<ObjectDescriptor*> children = desc->getChildren();
	int size =children.size();

	for(int i=0; i<size; ++i){
		recursiveDescriptorVisualize(children[i]);
	}	//chilren's descriptors visualize

	
}

void QControlContainer::controlContextChanged(){
	QMediator::getInstance()->graphEvent();
}

void QControlContainer::setDescriptor(ObjectDescriptor* desc){
	destroyInnerWidgets();
	curPosition=0;
	
	recursiveDescriptorVisualize(desc);

	GraphicLab* w = dynamic_cast<GraphicLab*>(frame->parentWidget());
	int size = innerWidgets.size();
	for(int i=0; i<size; i++){
		innerWidgets[i]->setParent(frame);
		innerWidgets[i]->show();
	}
	this->frame->resize(frame->frameRect().width(), curPosition+10);
}

void QControlContainer::singleDescriptorVisualize(ObjectDescriptor* desc){ // visualisation of class layer
	QLabel* classLabel = new QLabel(desc->getName(), frame);
	classLabel->setGeometry(QRect(10, curPosition, widgetWidth, 15));
	curPosition+=20;
	innerWidgets.push_back(classLabel);
	// name of class

	std::vector<IGraphProperty*> tempProperties = desc->getProperties();
	int size = tempProperties.size();
	QControlProperty* control;
	
	for(int i=0; i<size; ++i){
		control = new QControlProperty(tempProperties[i]);
		controlProperties.push_back(control);
		std::vector<QLabel*> labels;
		std::vector<QLineEdit*> edits;
		QLabel* mainLabel = control->getControls(labels, edits);

		if(mainLabel!=NULL){ // not a structured property
			//assert(mainLabel==NULL);
			mainLabel->setGeometry(QRect(10, curPosition, widgetWidth, 15));
			curPosition+=20;
			innerWidgets.push_back(mainLabel);
		}
		
		int size = edits.size();
		int sizeStat = labels.size();
		//assert(size==labels.size());

		for(int i=0; i<edits.size(); ++i){
			if(sizeStat==0){
				int a=9;
			}
			if(i<sizeStat){
				labels[i]->setGeometry(QRect(10, curPosition, widgetWidth, 15));
				innerWidgets.push_back(labels[i]);
			}
			edits[i]->setGeometry(QRect(widgetWidth+20, curPosition, widgetWidth, 15));
			innerWidgets.push_back(edits[i]);
			
			curPosition+=20;
			
		}
		delete tempProperties[i];
	}
	
}


void QControlContainer::destroyInnerWidgets(){
	int size = this->innerWidgets.size();
	for(int i=0; i<size; ++i){
		//delete innerWidgets[i];
		innerWidgets[i]->deleteLater();
	}
	innerWidgets.clear();

	size = this->controlProperties.size();
	for(int i=0; i<size; ++i){
		//delete controlProperties[i];
		delete controlProperties[i];
	}
	controlProperties.clear();
}

void QControlContainer::prepareToDestroyWidgets(){
	/*int size = this->innerWidgets.size();
	for(int i=0; i<size; ++i){
		innerWidgets[i]->;
	}
	innerWidgets.clear();

	size = this->controlProperties.size();
	for(int i=0; i<size; ++i){
		delete controlProperties[i];
	}
	controlProperties.clear();*/
}


QControlContainer* QControlContainer::instance = NULL;
QControlContainer* QControlContainer::getInstance(){return instance;}
void QControlContainer::init(QFrame* frame){instance = new QControlContainer(frame);}

//QControlContainer::QControlContainer(const QControlContainer&){
//}