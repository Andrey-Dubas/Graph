#include "IGraphContainer.h"
#include "QGraphContainer.h"
#include <QGraphicsScene>
#include "IGrapgEntity.h"


IGraphContainer* IGraphContainer::container;
void IGraphContainer::addPropertiesDescriptor(){

}


IGraphContainer::IGraphContainer(void){
}

IGraphContainer::~IGraphContainer(void){
	//std::vector<IGraphEntity*>::iterator it;

	IGraphEntity *tmp;
	for(int i=0; i<collection.size(); ++i){
		tmp = collection.front();
		//IGraphEntity* gr = new IGraphEntity(tmp);
		delete tmp;
	}
	collection.clear();
	

	/*this->ManageCollection.clear();
	for(int i=0; i<this->selectedCollection.size(); ++i){
		delete selectedCollection[i];
		this->selectedCollection.pop_back();
	}*/
}

bool IGraphContainer::pointAt(float x, float y){
	bool targeted = false;
	std::list<IGraphEntity*>::iterator it;
	this->selectedCollection.clear();
	for(it = this->collection.begin(); it!=this->collection.end(); ++it){
		if((*it)->pointIn(x, y)){
			this->selectedCollection.push_back(*it);
			targeted=true;
		}
	}
	
	
	return targeted;
}


IGraphContainer* IGraphContainer::getInstance(){
	return IGraphContainer::container;
}

void IGraphContainer::init(MyQGraphicsView* view, QPaintDevice* dev){
	container = new QGraphContainer(view, dev);
}