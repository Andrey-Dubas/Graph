#include "IGrapgEntity.h"
#include <memory>
#include "LayerGenerator.h"



IGraphEntity::IGraphEntity(const IGraphEntity& obj):InfoProvider((InfoProvider&)obj){

	std::list<IGraphLayer*>::const_iterator it = obj.LayerStack.begin();
	for(; it!=obj.LayerStack.end(); ++it){
		if(!(*it)->singleton()) this->LayerStack.push_front((*it)->clone());
	}
	origPos = obj.origPos;
	this->convertedPos = new CordContainer(obj.convertedPos->rows, obj.convertedPos->cols);
}

/*ElementContainer IGraphEntity::getDescriptionElements(){
	return ElementContainer();
}*/

ElementContainer IGraphEntity::getManageElements(){//not yet implemented
	return ElementContainer();
}


bool IGraphEntity::getPointedFace(point mouse, point& A, point& B, point& C){
	//char str[50];
	point** cords = convertedPos->Cords;
	for(int i=0; i<convertedPos->rows-1; ++i){
		for(int j=0; j<convertedPos->cols-1; ++j){
			bool isIn = isInTriangle(cords[i][j].x, cords[i][j].y, cords[i+1][j].x, cords[i+1][j].y,
						cords[i][j+1].x, cords[i][j+1].y, mouse.x, mouse.y);
			//sprintf(str, "[%4f : %4f : %4f ]\n", cords[i][j].x, cords[i][j].y, cords[i][j].z);
			//OutputDebugStringA(str);
			if(isIn==true){
				A = cords[i][j];
				B = cords[i][j+1];
				C = cords[i+1][j];
				return true;
			}

			isIn = isInTriangle(cords[i+1][j+1].x, cords[i+1][j+1].y, cords[i+1][j].x, cords[i+1][j].y,
						cords[i][j+1].x, cords[i][j+1].y, mouse.x, mouse.y);
			if(isIn==true){
				A = cords[i+1][j+1];
				B = cords[i][j+1];
				C = cords[i+1][j];
				return true;
			}
		}
	}
	return false;
}


IGraphEntity::IGraphEntity(void):convertedPos(NULL)
{
	additionalInfoDraw = false;
	std::list<IGraphLayer*> l = LayerGenerator::getInstance()->getSingletonLayers();
	for(std::list<IGraphLayer*>::iterator it = l.begin(); it!=l.end(); ++it){
		this->registerLayer(*it);
	}
	this->registerLayer(const_cast<ILayerFactory*>(LayerGenerator::getInstance())->getWorldConverter(point(0, 0, 0), point(0, 0, 0)));
	
	registerClassDescriptor();
	
}

IGraphEntity::~IGraphEntity(void)
{
	std::list<IGraphLayer*>::iterator it;
	for(it = LayerStack.begin(); it!=LayerStack.end(); it++){
		if(!(*it)->singleton()){ 
			delete *it;}
	}
}


void IGraphEntity::setParam(IGraphProperty* prop){
	InfoProvider::setParam(prop);
	this->process();
}


bool IGraphEntity::pointIn(float x, float y){
	if(isPointIn(x, y)){
		mousePosition = point(x, y, 0);
		return additionalInfoDraw = true;
	}
	return additionalInfoDraw = false;
}

void IGraphEntity::registerLayer(IGraphLayer* layer){
	bool inserted=false;
	std::list<IGraphLayer*>::iterator it;
	for(it=this->LayerStack.begin(); it!=this->LayerStack.end(); ++it){
		if(!(*it)->singleton()){
			if(*(*it)==*layer){
				delete *it;
				(*it)=layer;
				inserted=true;
			}
		}
		if(*(*it)<*layer){
			LayerStack.insert(it, layer);
			inserted=true;
		}
	}
	if(inserted==false){
		LayerStack.push_front(layer);
	}
}

void IGraphEntity::addPropertiesDescriptor(){
	std::list<IGraphLayer*>::iterator it;
	ObjectDescriptor *tmp;
	for(it = this->LayerStack.begin(); it!=this->LayerStack.end(); it++){
		tmp = new ObjectDescriptor((*it)->getDescriptor());
		descriptor->addChildren(tmp);
	}
}

void IGraphEntity::process(){
	std::list<IGraphLayer*>::iterator it;
	if(convertedPos!=NULL) delete convertedPos;

	CordContainer* buf_orig = new CordContainer(this->origPos);
	CordContainer* buf_processed = new CordContainer(this->origPos);
	
	for(it=LayerStack.begin(); it!=LayerStack.end(); ++it){
		(*it)->process(*buf_orig, *buf_processed);
		std::swap<CordContainer*>(buf_orig, buf_processed);
	}
	delete buf_processed;
	this->convertedPos = buf_orig;
}

void IGraphEntity::reverseProcess(){
	CordContainer* buf_orig = new CordContainer(*convertedPos);
	CordContainer* buf_processed = new CordContainer(*convertedPos);
	
	if(LayerStack.size()>0){
		std::list<IGraphLayer*>::iterator it=this->LayerStack.end();
		do{
			--it;
			(*it)->reverseProcess(*buf_orig, *buf_processed);
			std::swap<CordContainer*>(buf_orig, buf_processed);

		} while (it!=LayerStack.begin());
	}
	
	this->origPos = *buf_orig;

	delete buf_orig;
	delete buf_processed;
}

