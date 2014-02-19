#include "QMediator.h"


IMediator* QMediator::mediator = NULL;
void QMediator::graphEvent(){
	ObjectDescriptor desc = this->graph->getFullDescriptor();
	this->control->setDescriptor(&desc);
	graph->pictureParamsChanged();
}