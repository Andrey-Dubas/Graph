#include "IWorldConverter.h"
#include "IGraphProperty.h"
#include "NumProperty.h"
#include <stack>
#include "PointProperty.h"
#include "InfoProvider.h"

IWorldConverter::IWorldConverter(void):objectPos(0, 0, 0), objectOrientation(0, 0, 0), objectSpaceKoef(1, 1, 1)
{
	registerClassDescriptor();
}

IWorldConverter::IWorldConverter(point pos, point orientation):objectPos(pos), objectOrientation(orientation), objectSpaceKoef(1, 1, 1){
	registerClassDescriptor();
}

IWorldConverter::~IWorldConverter(void)
{
}

IWorldConverter::IWorldConverter(const IWorldConverter& obj){
	objectPos = obj.objectPos;
	objectOrientation = obj.objectOrientation;
	objectSpaceKoef = obj.objectSpaceKoef;
}


