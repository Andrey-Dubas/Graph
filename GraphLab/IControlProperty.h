#pragma once
#include "IGrapgEntity.h"
#include "IGraphProperty.h"
#include "ObjectDescriptor1.h"
#ifdef QT_CORE_LIB
	#include <QObject>
#endif
class IControlProperty// abstract
#ifdef QT_CORE_LIB
	: public QObject
#endif
{
#ifdef QT_CORE_LIB
	Q_OBJECT
#endif
protected:
	IGraphProperty* prop;
public:
	inline IGraphProperty* getProperty();
	IControlProperty(IGraphProperty* entity, QObject *parent = 0);
	virtual ~IControlProperty(void);
	IControlProperty(const IControlProperty &):QObject(0){}
private:
	IControlProperty operator=(const IControlProperty &);
	IControlProperty(void);
//public slots:
//	virtual void setPoint()=0;
//	virtual void setSingleValue()=0;
};
