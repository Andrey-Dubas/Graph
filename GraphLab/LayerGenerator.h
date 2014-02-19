#pragma once
#include "ILayerFactory.h"
#include "LayerFactory.h"
#include "TestLayerFactory.h"

class LayerGenerator
{
public:
	static const ILayerFactory* instance;
	static const ILayerFactory* getInstance(){return instance;}
};


