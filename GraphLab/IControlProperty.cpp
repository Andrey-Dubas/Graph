#include "IControlProperty.h"


IGraphProperty* IControlProperty::getProperty(){
	return prop;
}
IControlProperty::IControlProperty(IGraphProperty* entity, QObject *parent):QObject(parent){
	this->prop = entity->clone();
}

IControlProperty::IControlProperty(void):QObject(0)
{
}

IControlProperty::~IControlProperty(void){delete prop;}
