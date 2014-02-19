#include "IGraphProperty.h"
#include "InfoProvider.h"

void IGraphProperty::setProperty(){
	descriptee->setParam(this);
}