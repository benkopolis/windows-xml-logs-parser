#include "event.h"


Event::Event()
{
    _sessionId = 0;
    _occurenceTime = 0;
    _userId = 0;
    _eventType = 0;
}

Event::Event(int o, int s, int u)
{
    _sessionId = s;
    _occurenceTime = o;
    _userId = u;
    _eventType = 0;
}

Event::Event(const QString& o, const QString& s, const QString& u, const QString& t):
	_type(t)
{
    DataMapper* i = DataMapper::instance();
    QDateTime dt, bdt;
    bdt = QDateTime::fromString("2000-01-01T00:00:00", Qt::ISODate);
    dt = QDateTime::fromString(o, Qt::ISODate);
    _occurenceTime = dt.toTime_t() - bdt.toTime_t();
    bool ok = true;
    if(!i)
	ok = false;
    else
	ok = true;
    if(ok)
	_sessionId = i->id(s, t);
    else
	_sessionId = 0;
    if(ok)
	_userId = i->id(u, t);
    else
	_userId = 0;
    _eventType = 0;
}

QString Event::toString()
{
    QString result;
    QTextStream r(&result);
    r << _occurenceTime << "," << _sessionId << ":" << _eventType << "," << _userId;
    return result;
}
