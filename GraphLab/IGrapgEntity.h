#pragma once
#include "infoprovider.h"
#include "CordContainer.h"
#include "IGraphLayer.h"
#include "GraphicLib.h"
#include <list>

class IGraphEntity abstract:
	public InfoProvider{

protected:
	std::list<IGraphLayer*> LayerStack;
	CordContainer origPos;
	
	CordContainer* currentPos;
	CordContainer* OldPos;
	point mousePosition;
	bool  additionalInfoDraw;
	ElementContainer descriptionElements;
public:
	CordContainer* convertedPos;

	virtual void updateLayerInfo(){
		this->descriptor->clearChildren();
		std::list<IGraphLayer*>::iterator it;
		for(it = LayerStack.begin(); it!=LayerStack.end(); ++it){
			if((*it)->singleton()==false){
				this->descriptor->addChildren(new ObjectDescriptor((*it)->getDescriptor()));
			}
		}
	}
	IGraphEntity(const IGraphEntity& obj);

	virtual void setParam(IGraphProperty* prop);
	inline CordContainer* getPointToDraw() {
		return convertedPos;
	}

	void nativeConvert(){
		this->reverseProcess();
	}

	ElementContainer getDescriptionElements(){
		return descriptionElements;
	}
	void clearDescriptionElements(){
		ElementContainer::iterator it = descriptionElements.begin();
		for(; it!=descriptionElements.end(); it++){
			delete *it;
		}
		descriptionElements.clear();
	}

	virtual ElementContainer getManageElements();//not yet implemented

	bool getPointedFace(point mouse, point& A, point& B, point& C);
	
	virtual void processUpdate(float  movingProgress){
		InfoProvider::processUpdate(movingProgress);
		recalculateInitialData();
	}
	void basicParamsChanged();
	virtual void addPropertiesDescriptor();
	void process();
	void reverseProcess();
	IGraphEntity(void);
	virtual ~IGraphEntity(void);
	virtual bool isPointIn(float x, float y)=0; // point in object(in screen coordynate system)
	bool pointIn(float x, float y);
	void registerLayer(IGraphLayer*);
protected:
	virtual void additionalUpdate(float progress){
		for(std::list<IGraphLayer*>::iterator it=LayerStack.begin(); it!=LayerStack.end(); ++it){
			(*it)->processUpdate(progress);
		}
	};
	
	

};
