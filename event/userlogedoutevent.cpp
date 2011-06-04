#include "userlogedoutevent.h"


UserLogedOutEvent::UserLogedOutEvent():
	Event("", "", "", "UserLogedOut")
{
    this->_eventType = 4647;
}

UserLogedOutEvent::UserLogedOutEvent(const QString& time, const QString& session, const QString& user, const QString& targetUser,
				   const QString& targetSession):
	Event(time, session, user, "UserLogedOut")
{
    DataMapper* i = DataMapper::instance();
	this->_eventType = i->id("4647", this->_type);
	this->_TargetLogonId = i->id(targetSession, this->_type);
	this->_TargetUserName = i->id(targetUser, this->_type);
}

QString UserLogedOutEvent::toString()
{
    QString result;
    QTextStream r(&result);
    r << _occurenceTime << "," << _sessionId << ":" << _eventType << "," << _userId
	    << "," << _TargetUserName << "," << _TargetLogonId;
    return result;
}
