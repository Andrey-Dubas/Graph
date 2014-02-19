#pragma once
#include "IGraphProperty.h"
#include "GraphicLib.h"
#include "IGraphProperty.h"
#include "PointProperty.h"


class RefPointProperty;

class ValuePointProperty :
	public IGraphProperty
{
	friend class RefPointProperty;
protected:
	point innerPoint;
public:

	virtual void add(IGraphProperty* obj1, IGraphProperty* obj2){
		ValuePointProperty* conv1 = dynamic_cast<ValuePointProperty*>(obj1);
		ValuePointProperty* conv2 = dynamic_cast<ValuePointProperty*>(obj2);
		assert(conv1!=NULL&&conv2!=NULL);
		this->innerPoint = conv2->innerPoint + conv1->innerPoint;
	}

	virtual std::auto_ptr<IGraphProperty> mul(float obj){
		ValuePointProperty* ret = new ValuePointProperty(*this);
		ret->innerPoint = this->innerPoint*obj;
		return std::auto_ptr<IGraphProperty>(dynamic_cast<IGraphProperty*>(ret));
	}

	void setValue(point val){innerPoint = val;}
	point getValue(){return innerPoint;}

	ValuePointProperty(InfoProvider* descriptee, point p, UINT ID, const wchar_t* const name)
			:IGraphProperty(descriptee, ID,  name){
		innerPoint = point(p);
		valueSize = sizeof(point);
		this->pureValue = &innerPoint;
	}

	ValuePointProperty(InfoProvider* descriptee, point p, UINT ID)
			:IGraphProperty(descriptee, ID){
		innerPoint = p;
		valueSize = sizeof(p);
		this->pureValue=static_cast<void*>(&innerPoint);
	}

	void init(const ValuePointProperty& obj){
		innerPoint = obj.innerPoint;
		this->propertyID = obj.propertyID;
		delete [] displayName;
		displayName = new wchar_t[wcslen(obj.displayName)+1];
		wcscpy(displayName, obj.displayName);
	}

	const ValuePointProperty& operator=(const ValuePointProperty& obj){
		init(obj);
		return *this;
	}

	ValuePointProperty(InfoProvider* descriptee, const ValuePointProperty& obj):IGraphProperty(descriptee){
		init(obj);
	}

	virtual IGraphProperty* clone(){
		IGraphProperty* obj = new ValuePointProperty(descriptee, innerPoint, propertyID, displayName);
		return obj;
	}

	ValuePointProperty(InfoProvider* descriptee):IGraphProperty(descriptee){
		propertyID = -1;
		displayName = NULL;
	}

	//void
	virtual ~ValuePointProperty(void);
};


class RefPointProperty:
	public IGraphProperty{
		protected:
	point* innerPoint;
public:

	virtual void add(IGraphProperty* obj1, IGraphProperty* obj2){
		RefPointProperty* conv1 = dynamic_cast<RefPointProperty*>(obj1);
		RefPointProperty* conv2 = dynamic_cast<RefPointProperty*>(obj2);
		if(conv1!=NULL&&conv2!=NULL){
			*this->innerPoint = *conv2->innerPoint + *conv1->innerPoint;
		}
		ValuePointProperty* conv1_2 = dynamic_cast<ValuePointProperty*>(obj1);
		ValuePointProperty* conv2_2 = dynamic_cast<ValuePointProperty*>(obj2);
		if(conv1_2!=NULL&&conv2_2!=NULL){
			*this->innerPoint = conv2_2->innerPoint + conv1_2->innerPoint;
		}
	}

	virtual std::auto_ptr<IGraphProperty> mul(float obj){
		RefPointProperty* ret = new RefPointProperty(*this);
		*(ret->innerPoint) = *(this->innerPoint)*obj;
		return std::auto_ptr<IGraphProperty>(dynamic_cast<IGraphProperty*>(ret));
	}

	/*const RefPointProperty operator=(const ValuePointProperty& obj){
		memcpy(this->pureValue, obj.getValue());
	}*/

	RefPointProperty(point& p, UINT ID){
		this->valueSize = sizeof(p);
		this->propertyID = ID;
		//innerPoint = new point(p);
		this->pureValue = &p;
		innerPoint = &p;
		//this->valueSize = sizeof(point);
	}

	RefPointProperty(){
		this->valueSize = sizeof(point);
		this->pureValue = malloc(valueSize);
	}

	void init(const RefPointProperty& obj){
		*(this->innerPoint) = *obj.innerPoint;
		this->propertyID = obj.propertyID;
	}

	const RefPointProperty& operator=(const RefPointProperty& obj){
		init(obj);
		return *this;
	}

	RefPointProperty(const RefPointProperty& obj):IGraphProperty(obj){
		this->valueSize = sizeof(innerPoint);
		innerPoint = static_cast<point*>(pureValue);
		init(obj);
	}

	virtual IGraphProperty* clone(){
		RefPointProperty* obj = new RefPointProperty(*innerPoint, propertyID);
		return obj;
	}

	virtual ~RefPointProperty(void){};
};