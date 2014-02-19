#pragma once
#include "IGraphProperty.h"
#include "GraphicLib.h"

template <typename ContainedType> class RefNumProperty;

template <typename ContainedType>
class ValueNumProperty :
	public IGraphProperty
{
	friend class RefNumProperty<ContainedType>;
private:
	//static const size_t valueSize = sizeof(ContainedType);
	friend ValueNumProperty<ContainedType> operator+(const ValueNumProperty<ContainedType>& obj1, const ValueNumProperty<ContainedType>& obj2);
protected:
	ContainedType value;
	ContainedType upperValue, lowerValue;
	ContainedType discreteValue; // set this attribute to zero for non-discrete attr.
public:

	virtual void add(IGraphProperty* obj1, IGraphProperty* obj2){
		ValueNumProperty<ContainedType>* conv1 = dynamic_cast<ValueNumProperty<ContainedType>*>(obj1);
		ValueNumProperty<ContainedType>* conv2 = dynamic_cast<ValueNumProperty<ContainedType>*>(obj2);
		assert(conv1!=NULL&&conv2!=NULL);
		this->value = conv2->value + conv1->value;
	}

	virtual std::auto_ptr<IGraphProperty> mul(float obj){
		ValueNumProperty<ContainedType>* ret = new ValueNumProperty<ContainedType>(*this);
		ret->value = this->value*obj;
		return std::auto_ptr<IGraphProperty>(dynamic_cast<IGraphProperty*>(ret));
	}

	ContainedType getMax(){ return upperValue;}
	void setMax(ContainedType upper){ upperValue = upper;}

	ContainedType getMin(){ return lowerValue;}
	void setMin(ContainedType lower){ lowerValue = lower;}

	void setValue(ContainedType val){
		if((val<upperValue)&&(val>lowerValue)){
			value = val;
		}
		else throw LPSTR("value could not be setted");
	}

	inline ContainedType getValue() { return value;}

	void init(InfoProvider* descriptee, ContainedType iniVal){
		this->descriptee = descriptee;
		value = iniVal;
		valueSize = sizeof(ContainedType);
		pureValue = &value;
	}

	ValueNumProperty(InfoProvider *descriptee, ContainedType iniVal, UINT ID, const wchar_t*const name):IGraphProperty(descriptee, ID, name), upperValue(0xFFFF), lowerValue(-100000){
		init(descriptee, iniVal);
	}
	

	ValueNumProperty(InfoProvider* descriptee, ContainedType iniVal, UINT ID, const wchar_t*const name, ContainedType upperVal, ContainedType lowerVal):IGraphProperty(descriptee, ID, name){
		init(iniVal);
		//if((lowerVal=<iniVal) && (iniVal>=upperVal)){
		value = iniVal;
		upperValue = upperVal; lowerValue = lowerVal;
		//}
		if(value<lowerValue){
			throw PROPERTY_EXCEPTION(L"value is lower than low limit");
		}
		if(value>upperValue){
			throw PROPERTY_EXCEPTION(L"value is bigger than high limit");
		}
	}

	void init(const ValueNumProperty& obj){
		this->descriptee = obj.descriptee;
		this->value = obj.value;
		this->propertyID = obj.propertyID;
		delete this->displayName;
		this->displayName = new wchar_t[wcslen(obj.displayName)+1];
		wcscpy(displayName, obj.displayName);
		valueSize = sizeof(ContainedType);
		this->pureValue = &value;
		upperValue = obj.upperValue; lowerValue = obj.lowerValue;
		discreteValue = obj.discreteValue; // set this attribute to zero for non-discrete attr.
	}

	ValueNumProperty(const ValueNumProperty& obj){
		init(obj);
	}

	virtual const ValueNumProperty& operator=(const ValueNumProperty& obj){
		init(obj);
		return *this;
	}

	virtual IGraphProperty* clone(){
		IGraphProperty* obj = new ValueNumProperty<ContainedType>(*this);
		return obj;
	}

	virtual ~ValueNumProperty(void)
	{
	}

	const ValueNumProperty& operator/(const float num){
		this->value = this->value/num;
		return *this;
	}
	
};

template<typename T>
ValueNumProperty<T> operator+(const ValueNumProperty<T>& obj1, const ValueNumProperty<T>& obj2){
	ValueNumProperty ret(obj1);
	ret->value += obj2->value;
	return *ret;
}

typedef ValueNumProperty<int> ValueIntProperty;
typedef ValueNumProperty<float> ValueFloatProperty;



/*object for changing attribute in class*/
template <typename ContainedType>
class RefNumProperty :
	public IGraphProperty
{
protected:
	ContainedType* value;
public:
	virtual void add(IGraphProperty* obj1, IGraphProperty* obj2){
		RefNumProperty<ContainedType>* conv1 = dynamic_cast<RefNumProperty<ContainedType>*>(obj1);
		RefNumProperty<ContainedType>* conv2 = dynamic_cast<RefNumProperty<ContainedType>*>(obj2);
		if(conv1!=NULL&&conv2!=NULL){
			*(this->value) = *(conv2->value) + *(conv1->value);
		}
		ValueNumProperty<ContainedType>* conv1_2 = dynamic_cast<ValueNumProperty<ContainedType>*>(obj1);
		ValueNumProperty<ContainedType>* conv2_2 = dynamic_cast<ValueNumProperty<ContainedType>*>(obj2);
		if(conv1_2!=NULL&&conv2_2!=NULL){
			*(this->value) = conv2_2->value + conv1_2->value;
		}
	}

	virtual std::auto_ptr<IGraphProperty> mul(float obj){
		RefNumProperty* ret = new RefNumProperty(*this);
		*(ret->value) = *(this->value)*obj;
		return std::auto_ptr<IGraphProperty>(dynamic_cast<IGraphProperty*>(ret));
	}

	ContainedType getValue(){return this->value;}
	virtual IGraphProperty* clone(){
		RefNumProperty* obj = new RefNumProperty(*value, propertyID);
		return obj;
	}

	/*const RefNumProperty<ContainedType> operator=(const ValueNumProperty<ContainedType>& obj){
		*(this->pureValue) = obj.getValue();
	}*/

	/*virtual IGraphProperty* clone(){
		return RefNumProperty<ContainedType>
	}*/

	RefNumProperty(ContainedType& val, UINT ID){
		this->propertyID = ID;
		value = &val;
		pureValue = value;
		this->valueSize = sizeof(val);
	}

	const RefNumProperty<ContainedType> operator=(const ValueNumProperty<ContainedType>& obj){
		*(this->value) = obj.value;
		return *this;
	}

	virtual ~RefNumProperty(void)
	{
	}

	void init(const RefNumProperty<ContainedType>& obj){
		this->descriptee = obj.descriptee;
		if(pureValue==NULL){
			this->valueSize = obj.valueSize;
			pureValue = malloc(valueSize);
			value = (ContainedType*)pureValue;
		}
		memcpy(this->pureValue, obj.pureValue, obj.valueSize);
		this->propertyID = obj.propertyID;
		if(displayName!=NULL){
			delete [] displayName;
		}
		if(obj.displayName!=NULL){
			displayName = new wchar_t[wcslen(obj.displayName)+1];
			wcscpy(displayName, obj.displayName);
		}
	}

	RefNumProperty<ContainedType> operator=(const RefNumProperty<ContainedType>& obj){
		init(obj);
		return *this;
	}

	RefNumProperty(const RefNumProperty<ContainedType>& obj){
		this->valueSize = sizeof(*(this->value));
		init(obj);
	}

	RefNumProperty<ContainedType> operator=(ValueNumProperty<ContainedType> obj){
		*(this->value) = obj.value;
		this->propertyID = obj.propertyID;
		delete this->displayName;
		this->displayName = new wchar_t[wcslen(obj.displayName)+1];
		wcscpy(displayName, obj.displayName);
		return *this;
	}


	const RefNumProperty& operator/(const float num){
		*this->value = *this->value/num;
		return *this;
	}
	

};

template<typename T>
RefNumProperty<T> operator+(const RefNumProperty<T>& obj1, const RefNumProperty<T>& obj2){
	RefNumProperty<T> ret=obj1.clone();
	*this->value = *obj1->value + *obj2->value;
	return *this;
}

typedef RefNumProperty<float> RefFloatProperty;
typedef RefNumProperty<int> RefIntProperty;

#define REF_PROP_FLOAT(VAL, ID) RefFloatProperty(*(VAL), L###VAL, ID)
#define REF_PROP_INT(VAL, ID) RefIntProperty(*(VAL), L###VAL, ID)

