#pragma once
#include "infoprovider.h"
#include "CordContainer.h"

#include "GraphicLib.h"
#include "IGraphContainer.h"


class IGraphEntity;

class SingletonException: public Exception{
public:
	SingletonException(const wchar_t* mess, const char* func, const unsigned int row):
			Exception(mess, func, row){
	}
};

class IGraphLayer :
	public InfoProvider
{
protected:
	bool changed;
	const CordContainer* originalPos;
	CordContainer* convertedPos;
	IGraphEntity* object;
public:
	void setObject(IGraphEntity* obj){object = obj;}
	virtual IGraphLayer* clone()=0;
	virtual bool singleton() const=0;
	virtual UINT priority() const {return unsigned(-1);};
	virtual bool operator<(IGraphLayer obj){
		return (this->priority())<(obj.priority());
	}
	virtual bool operator==(IGraphLayer obj){
		return (this->priority())==(obj.priority());
	}
	virtual void addPropertiesDescriptor();
	IGraphLayer(void);
	IGraphLayer(const IGraphLayer& obj);
	virtual ~IGraphLayer(void);

	void process(const CordContainer &origCords, CordContainer &convertedCords);
	void reverseProcess(const CordContainer &origCords, CordContainer &convertedCords);
protected:
	virtual void process()=0;	//compute cords
	virtual void reverseProcess()=0;

	//virtual void InvokeProcessForward()=0;
	//virtual void InvokeProcessBackward()=0;

	virtual void preProcessForward()=0;	//compute matrix
	virtual void preProcessBackward()=0;

	
};

#define PRIORITY(priorityValue) inline virtual unsigned int priority() const { return priorityValue;}
#define SINGLETON(BOOLEAN) virtual bool singleton() const{return BOOLEAN;}
#define NOT_CLONNABLE virtual IGraphLayer* clone() {\
	return this;\
}
