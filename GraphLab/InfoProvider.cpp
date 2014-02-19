#include "Observer.h"

#include "IWorldConverter.h"

void InfoProvider::setParam(IGraphProperty* prop){
	if(dynamic_cast<IWorldConverter*>(this)!=NULL){
		int a=6;
	}
	for(size_t i=0; i<propertiesCount; ++i){
		*previousPropertiesList[i] = *propertiesList[i]; // if updating values - save current position as starting point
		if(*(nextPropertiesList[i])==*prop){
			*(nextPropertiesList[i])=*prop;
			this->descriptor->updateProperty(prop);
		}
	}
	recalculateInitialData(); // recalculace original cords
}

void InfoProvider::processUpdate(float  movingProgress){
	for(int i=0; i<propertiesCount; ++i){
		propertiesList[i]->add(nextPropertiesList[i]->mul(movingProgress*1.).get(), previousPropertiesList[i]->mul(1.-movingProgress).get());
	}
	if( movingProgress>=1.){
		for(int i=0; i<propertiesCount; ++i){
			*previousPropertiesList[i] = *nextPropertiesList[i];
		}
	}
	additionalUpdate(movingProgress);
}

InfoProvider::InfoProvider(void):propertiesCount(0), counterID(0), propertiesList(NULL)
{
	previousDescriptor=NULL;
	registerClassDescriptor();
}

InfoProvider::InfoProvider(const InfoProvider& obj){
	this->descriptor = new ObjectDescriptor(*obj.descriptor);
	this->propertiesCount = obj.propertiesCount;
	propertiesList = new IGraphProperty*[propertiesCount];
	previousPropertiesList = new IGraphProperty*[propertiesCount];
	nextPropertiesList = new IGraphProperty*[propertiesCount];
	for(size_t i=0; i<propertiesCount; ++i){
		propertiesList[i] = obj.propertiesList[i]->clone();
		nextPropertiesList[i] = obj.nextPropertiesList[i]->clone();
		previousPropertiesList[i] = obj.previousPropertiesList[i]->clone();
	}
}



InfoProvider::~InfoProvider(void)
{
	for(int i=0; i<this->propertiesCount; ++i){
		delete propertiesList[i];
		delete nextPropertiesList[i];
		delete previousPropertiesList[i];
	}
	if(propertiesList!=NULL){
		delete [] propertiesList;
		delete [] previousPropertiesList;
		delete [] nextPropertiesList;
	}
}


