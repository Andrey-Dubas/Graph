#pragma once
#include <vector>
#include "ObjectDescriptor1.h"
#include "GraphicLib.h"
#include <typeinfo>

class InfoProvider abstract
{
public:
	
	
protected:
	ObjectDescriptor* descriptor;		 // object represent class and contained classes
	ObjectDescriptor *previousDescriptor; // parent class 
	IGraphProperty **propertiesList; // internal array of pairs <id, pointer on property>
	IGraphProperty **previousPropertiesList;
	IGraphProperty **nextPropertiesList;
	std::vector<IGraphProperty*> temp; 
	int propertiesCount;//
	//float movingProgress;  // value [0..1], descripts the process of turning cords
	UINT counterID;// ID of next pointer
public:
	virtual void updateLayerInfo(){
	}
	virtual void processUpdate(float  movingProgress);

	InfoProvider(const InfoProvider& obj);
protected:

	virtual void additionalUpdate(float progress){};
	
	virtual void addPropertiesDescriptor(){ // redefine this property in each
	}										// inherit class. registerValue will 
											// recursively makes descriptors
											// when constructors call. Use it carefully,
											// this is a little mind-boggling!!!!!


	virtual void registerClassDescriptor(){						// Make it call all constructorsfrom constructor.
																// Don't change it!
		descriptor = new ObjectDescriptor(this, typeid(*this).name(), previousDescriptor);
		descriptor->lowerClassDescriptor = previousDescriptor;	
		addPropertiesDescriptor();
		previousDescriptor = descriptor;
	};

public:
	virtual ObjectDescriptor getDescriptor(){
		return *descriptor;
	} 
		// get all info about object and its children


	virtual void recalculateInitialData()=0;

	virtual void setParam(IGraphProperty* prop);
		// set property of object

	InfoProvider(void);
	virtual ~InfoProvider(void);
	//new ValuePointProperty(
};


#define ADD_PROPERTY_START() virtual void addPropertiesDescriptor(){

#define ADD_PROPERTY(TYPE, VAL, NAME)\
		descriptor->addProperty(new Value##TYPE(this, VAL, ++counterID, L##NAME));\
		temp.push_back(new Ref##TYPE(VAL, counterID));\
		temp.push_back(new Value##TYPE(this, VAL, counterID, L""));\
		temp.push_back(new Value##TYPE(this, VAL, counterID, L""));



#define ADD_PROPERTY_END()\
		propertiesCount = temp.size();\
		propertiesList =  new IGraphProperty*[propertiesCount];\
		previousPropertiesList = new IGraphProperty*[propertiesCount];\
		nextPropertiesList = new IGraphProperty*[propertiesCount];\
		int i=0;\
		for(int i=0; i<propertiesCount/3; i++){\
			propertiesList[i] = temp[3*i];\
			nextPropertiesList[i] = temp[3*i+1];\
			previousPropertiesList[i] = temp[3*i+2];\
		}\
		propertiesCount/=3;\
	}