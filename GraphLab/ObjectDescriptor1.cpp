#include "ObjectDescriptor1.h"
#include <wchar.h>
#include "InfoProvider.h"

ObjectDescriptor::ObjectDescriptor(InfoProvider* descriptee, const char* Name, ObjectDescriptor* obj, std::vector<ObjectDescriptor*> _childDescriptors,
								PropertyContainer _properties):	lowerClassDescriptor(obj){
	this->descriptee = descriptee;
	this->childDescriptors = _childDescriptors;
	this->properties = _properties;
	className = new char[strlen(Name)+1];
	strcpy(this->className, Name);
}


ObjectDescriptor::ObjectDescriptor(InfoProvider* descriptee, const char* Name, ObjectDescriptor* obj)
: lowerClassDescriptor(obj){
	this->descriptee = descriptee;
	className = new char[strlen(Name)+1];
	strcpy(this->className, Name);
}


ObjectDescriptor::ObjectDescriptor(void){
	className=NULL;
	this->lowerClassDescriptor = NULL;
}

const char* ObjectDescriptor::getName() const{
	return className;
}


ObjectDescriptor::~ObjectDescriptor(void)
{
	if(lowerClassDescriptor!=NULL){
		delete lowerClassDescriptor;
		lowerClassDescriptor=NULL;
	}
	for(int i=0; i<childDescriptors.size(); ++i){
		delete this->childDescriptors[i];
	}

	for(int i=0; i<this->properties.size(); ++i){
		delete this->properties[i];
	}

	delete[] className;

}


bool ObjectDescriptor::updateProperty(IGraphProperty* prop){
	int size = properties.size();
	for(int i=0; i<size; ++i){
		if(*(properties[i]) == *prop){
			(*properties[i])=*prop;
			return true;
		}
	}
	if(this->getPrevious()!=NULL){
		this->getPrevious()->updateProperty(prop);
	}
	//this->descriptee->setParam(prop);
	return false;
}

void ObjectDescriptor::init(const ObjectDescriptor& obj){
	this->descriptee = obj.descriptee;
	lowerClassDescriptor= (obj.lowerClassDescriptor==NULL)||(obj.lowerClassDescriptor==&obj) ? NULL 
		: new ObjectDescriptor(*(obj.lowerClassDescriptor));
	
	for(int i=0; i<obj.childDescriptors.size(); ++i){
		this->addChildren(new ObjectDescriptor(*obj.childDescriptors[i]));
	}
	
	int s = obj.properties.size();
	for(int i=0; i<s; ++i){
		//this->addProperty(obj.properties[i]->clone());
		this->properties.push_back(obj.properties[i]->clone());
	}

	className = new char[strlen(obj.className)+1];
	strcpy(this->className, obj.className);
	
}

ObjectDescriptor& ObjectDescriptor::operator=(const ObjectDescriptor& obj){
	init(obj);
	return *this;
}

ObjectDescriptor::ObjectDescriptor(const ObjectDescriptor& obj){
	init(obj);
	
}


