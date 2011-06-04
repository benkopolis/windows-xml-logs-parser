#include "userlogedinevent.h"
#include <QTextStream>

UserLogedInEvent::UserLogedInEvent():
	Event("", "", "", "UserLogedIn")
{
    this->_eventType = 4624;
}

UserLogedInEvent::UserLogedInEvent(const QString& time, const QString& session, const QString& user, const QString& targetUser,
				   const QString& targetSession, const QString& logonType, const QString& ip, const QString& port):
	Event(time, session, user, "UserLogedIn")
{
    DataMapper* i = DataMapper::instance();
	this->_eventType = i->id("4624", this->_type);
	this->_TargetLogonId = i->id(targetSession, this->_type);
	this->_TargetUserName = i->id(targetUser, this->_type);
	this->_LogonType = i->id(logonType, this->_type);
	this->_IpAddress = i->id(ip, this->_type);
	this->_IpPort = i->id(port, this->_type);
}

QString UserLogedInEvent::toString()
{
    QString result;
    QTextStream r(&result);
    r << _occurenceTime << "," << _sessionId << ":" << _eventType << "," << _userId
	    << "," << _TargetUserName << "," << _TargetLogonId << "," << _LogonType
	    << "," << _IpAddress << "," << _IpPort;
    return result;
}
