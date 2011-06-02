#include "newprocesscreationevent.h"

NewProcessCreationEvent::NewProcessCreationEvent():
		Event("", "", "", "NewProcessCreation")
{
    this->_eventType = 4688;
}

NewProcessCreationEvent::NewProcessCreationEvent(const QString& time, const QString& session, const QString& user,
						 const QString& newProcess, const QString& oldProcess,
						 const QString& newProcessName):
	Event(time, session, user, "NewProcessCreation")
{
    this->_eventType = 4624;
    DataMapper* i = DataMapper::instance();
	this->_NewProcessId = i->id(newProcess, this->_type);
	this->_NewProcessName = i->id(newProcessName, this->_type);
	this->_ProcessId = i->id(oldProcess, this->_type);
}

QString NewProcessCreationEvent::toString()
{
    QString result;
    QTextStream r(&result);
    r << _occurenceTime << "," << _sessionId << ":" << _eventType << "," << _userId
	    << "," << _NewProcessId << "," << _ProcessId << "," << _NewProcessName;
    return result;
}
