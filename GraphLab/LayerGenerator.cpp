#include "LayerGenerator.h"

/*#ifdef CPPUNIT_TEST
const ILayerFactory* LayerGenerator::instance = new TestLayerFactory();
#endif

#ifndef CPPUNIT_TEST
*/const ILayerFactory* LayerGenerator::instance = new LayerFactory();
//#endif
