#include "processendedevent.h"

ProcessEndedEvent::ProcessEndedEvent():
	Event("", "", "", "ProcessEnded")
{
    this->_eventType = 4689;
}

ProcessEndedEvent::ProcessEndedEvent(const QString& time, const QString& session, const QString& user,
						 const QString& process, const QString& status,
						 const QString& processName):
	Event(time, session, user, "ProcessEnded")
{
    this->_eventType = 4624;
    DataMapper* i = DataMapper::instance();
	this->_ProcessId = i->id(process, this->_type);
	this->_ProcessName = i->id(processName, this->_type);
	this->_Status = i->id(status, this->_type);
}

QString ProcessEndedEvent::toString()
{
    QString result;
    QTextStream r(&result);
    r << _occurenceTime << "," << _sessionId << ":" << _eventType << "," << _userId
	    << "," << _ProcessId << "," << _Status << "," << _ProcessName;
    return result;
}
