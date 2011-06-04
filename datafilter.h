#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <QObject>
#include "configuration.h"
#include "event/event.h"
#include <QStringList>
#include <QMultiHash>

class DataFilter : public QObject
{
Q_OBJECT
public:
    explicit DataFilter(QObject *parent = 0);
	explicit DataFilter(Configuration* c, QObject *parent = 0);

	/**
	  * This method calls Configuration::instance() to get the configuration.
	  * Then it passes instance of Configuration object to method initialize with argument of
	  * Configuration* type.
	  */
	void initialize();
	/**
	  * This method extracts informations which are essential for
	  * filtering events.
	  */
	void initialize(Configuration* c);

	inline QStringList& attribs() { return _attribs; }
	inline QMultiHash<QString, QString>& attribsAndValues() { return _attribsAndValues; }
	inline uint youngerThen() const { return _youngerThen; }
	inline uint olderThen() const { return _olderThen; }

signals:

public slots:

protected:

	uint _youngerThen;
	uint _olderThen;
	QStringList _attribs;
	QMultiHash<QString, QString> _attribsAndValues;


};

#endif // DATAFILTER_H
