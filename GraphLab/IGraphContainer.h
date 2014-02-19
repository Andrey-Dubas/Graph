#pragma once
#include <vector>
#include "InfoProvider.h"
#include "QGraphicsModel.h"
#include <QTimer>

class MyQGraphicsView;
class IGraphEntity;
typedef std::list<IGraphEntity*> ElementContainer;

class IGraphContainer: public InfoProvider
{
protected:
	QTimer timer;
	std::list<IGraphEntity*> collection;
	std::list<IGraphEntity*> selectedCollection;
	std::list<IGraphEntity*> ManageCollection;
protected:
	virtual void addPropertiesDescriptor();
	static IGraphContainer* container;
public:
	static IGraphContainer* getInstance();
	static void init(MyQGraphicsView* view, QPaintDevice* dev);
	/*virtual void star(){
		
	}*/

	virtual void pictureParamsChanged()=0;
	virtual void clear()=0;
	virtual void draw()=0;
	virtual void drawPrepare()=0;
	virtual void recalculateInitialData(void) override{};
	bool pointAt(float x, float y);
	IGraphContainer(void);
	virtual ObjectDescriptor getFullDescriptor()=0;
	virtual ~IGraphContainer(void);
private:
	IGraphContainer(const IGraphContainer& obj);
	IGraphContainer& operator=(const IGraphContainer& );
};


