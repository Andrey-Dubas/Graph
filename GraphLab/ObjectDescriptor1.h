#pragma once
#include <stack>
#include "IGraphProperty.h"
//#include "InfoProvider.h"
//#include "IGraphLayer.h"
//class ObjectDescriptor;
#define ObjectDescriptorA(OBJ, CHILREN, PROPERTIES)\
	ObjectDescriptor(__CLASS__, OBJ, CHILREN, PROPERTIES)

typedef std::vector<IGraphProperty*> PropertyContainer;


class InfoProvider;
/*
message entity which fully presents whole object and internal objects
*/
class ObjectDescriptor{

public:
	ObjectDescriptor* lowerClassDescriptor;
	//HACK!!! remove it to protected!!
protected:
	
	InfoProvider* descriptee;
	char* className;
	
	std::vector<ObjectDescriptor*> childDescriptors;
	PropertyContainer properties;
public:
	ObjectDescriptor* getPrevious(){
		/*std::vector<ObjectDescriptor*> result;
		size_t size = childDescriptors.size();
		for(size_t i=0; i<size; ++i){
			result.push_back(new ObjectDescriptor(*childDescriptors[i]));
		}*/
		return lowerClassDescriptor;
	}

	std::vector<ObjectDescriptor*> getChildren(){return childDescriptors;}
	PropertyContainer getProperties(){
		PropertyContainer result;
		size_t size = properties.size();
		for(size_t i=0; i<size; ++i){
			result.push_back(properties[i]->clone());
		}
		return result;
	}
	const char* getName() const;
	void addChildren(ObjectDescriptor* addable){
		childDescriptors.push_back(addable);
	}

	void clearChildren(){
		for(int i=0; i<childDescriptors.size(); ++i){
			delete childDescriptors[i];
		}
		childDescriptors.clear();
	}
	
	void addProperty(IGraphProperty* addable){
		properties.push_back(addable);
	}

	ObjectDescriptor(void);

	ObjectDescriptor(InfoProvider* descriptee, const char* Name, ObjectDescriptor* obj, std::vector<ObjectDescriptor*> _childDescriptors, PropertyContainer properties);
	ObjectDescriptor(InfoProvider* descriptee, const char* Name, ObjectDescriptor* obj);
	virtual ~ObjectDescriptor(void);
	bool updateProperty(IGraphProperty* prop);

	ObjectDescriptor& operator=(const ObjectDescriptor& obj);
	ObjectDescriptor(const ObjectDescriptor& obj);
protected:
private:
	void init(const ObjectDescriptor& obj);
};
