#pragma once
#include "string.h"
#include <vector>
#include <windows.h>
#include <assert.h>
#include <typeinfo>

//#include "ObjectDescriptor1.h"
class InfoProvider;
class Objectdescriptor;
/*
 Elementary message describe value type of object.
 in GUI creates text-based value editor.
 TODO: any fasade for isolating model system from GUI.
*/
class IGraphProperty{
protected:
	InfoProvider* descriptee;
	UINT propertyID;		// object property identification
	wchar_t* displayName;   //name of property
	void* pureValue;
	//static const size_t valueSize;
	size_t valueSize;
public:

	virtual void add(IGraphProperty* obj1, IGraphProperty* obj2)=0;
	virtual std::auto_ptr<IGraphProperty> mul(float obj)=0;

	IGraphProperty(){
		pureValue=NULL;
		this->descriptee = NULL;
		displayName = NULL;
		propertyID = 0;
	}

	IGraphProperty(InfoProvider* descriptee){
		pureValue=NULL;
		this->descriptee = descriptee;
		displayName = NULL;
		propertyID = 0;
	}

	IGraphProperty(InfoProvider* descriptee, UINT ID){
		pureValue=NULL;
		this->descriptee = descriptee;
		displayName = NULL;
		propertyID = ID;
	}

	virtual bool operator==(const IGraphProperty& prop){
		return this->propertyID == prop.propertyID;
	}

	IGraphProperty(InfoProvider* descriptee, UINT ID, const wchar_t*const name){
		pureValue=NULL;
		this->descriptee = descriptee;
		displayName = new wchar_t[wcslen(name)+1];
		wcscpy(displayName, name);
		propertyID = ID;
	}

	void basicPropertyInit(const IGraphProperty& prop){
		this->descriptee = prop.descriptee;
		valueSize = prop.valueSize;
		if(pureValue==NULL){
			this->pureValue = malloc(valueSize);
		}
		memcpy(pureValue, prop.pureValue, valueSize);
		/*delete [] displayName;
		if(prop.displayName!=NULL){
			this->displayName = new wchar_t[wcslen(prop.displayName)+1];
			wcscpy(displayName, prop.displayName);
		}*/
	}

	virtual const IGraphProperty& operator=(const IGraphProperty& prop){
		if(this!=&prop){
			//assert(valueSize==prop.valueSize);

			basicPropertyInit(prop);
		}
		return *this;
	}

	IGraphProperty(const IGraphProperty& prop){
		displayName = NULL;
		valueSize = prop.valueSize;
		pureValue=NULL;
		basicPropertyInit(prop);
	}

	inline UINT getProperty() {return propertyID;}


	inline const wchar_t* getName() {return displayName;} 

	virtual IGraphProperty* clone()=0;//{ // the problem is to create object of the same type (in vector we keep 
								 // references to the polymorphic type, and it should be exhanged with another one)

	void setProperty();

	virtual ~IGraphProperty(void){
		delete[] displayName;
	}
};
