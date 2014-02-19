#include "IGraphLayer.h"
#include "ObjectDescriptor1.h"
#include "GraphicLib.h"
IGraphLayer::IGraphLayer(void)
{
}

IGraphLayer::IGraphLayer(const IGraphLayer& obj){
	this->originalPos = obj.originalPos;
}

IGraphLayer::~IGraphLayer(void)
{
}

void IGraphLayer::addPropertiesDescriptor(){
}

void IGraphLayer::process(const CordContainer &origCords, CordContainer &convertedCords){
	this->originalPos = &origCords;
	this->convertedPos = &convertedCords;
	this->preProcessForward();
	this->process();
}

void IGraphLayer::reverseProcess(const CordContainer &origCords, CordContainer &convertedCords){
	this->originalPos = &origCords;
	this->convertedPos = &convertedCords;
	this->reverseProcess();
	
}
