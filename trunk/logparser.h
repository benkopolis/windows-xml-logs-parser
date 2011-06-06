#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <QObject>
#include <QtXml/QXmlStreamReader>
#include "commons/exception.h"
#include "eventsparsers/parsers.h"
#include <QHash>
#include <QList>

/**
  * This class reads xml and calls proper parsers when encountered
  * one of parsed events. It also stores events and allows to save them.
  */
class LogParser : public QObject
{
Q_OBJECT
public:
    explicit LogParser(QObject *parent = 0);
    virtual ~LogParser();

signals:

public slots:

    void parse(QIODevice* device);
    bool addEventParser(EventParser* p);
    bool saveEvents(QIODevice* device);

protected:

    QHash<int, EventParser* > _parsers;
    QList<Event* > _events;


};

#endif // LOGPARSER_H
