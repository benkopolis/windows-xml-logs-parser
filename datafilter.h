#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <QObject>
#include "configuration.h"
#include "event/event.h"
#include <QStringList>
#include <QVariantMap>

class DataFilter : public QObject
{
Q_OBJECT
public:
    explicit DataFilter(QObject *parent = 0);

	inline QStringList acceptedAttribs() const { return _attribs; }
	inline QVariantMap acceptedAttribsAndValues() const { return _attribsAndValues; }
	inline uint yungerThen() const { return _yungerThen; }
	inline uint olderThen() const { return _olderThen; }

signals:

public slots:

protected:

	uint _yungerThen;
	uint _olderThen;
	QStringList _attribs;
	QVariantMap _attribsAndValues;


};

#endif // DATAFILTER_H
