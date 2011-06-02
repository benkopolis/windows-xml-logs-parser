#ifndef USERLOGEDINEVENT_H
#define USERLOGEDINEVENT_H

#include "event.h"

class UserLogedInEvent : public Event
{
protected:
    UserLogedInEvent();

public:
    UserLogedInEvent(const QString& time, const QString& session, const QString& user, const QString& targetUser,
		     const QString& targetSession, const QString& logonType, const QString& ip, const QString& port);

    inline int targetUserName() const { return _TargetUserName; }
    inline int targetLogonId() const { return _TargetLogonId; }
    inline int logonType() const { return _LogonType; }
    inline int ipAddress() const { return _IpAddress; }
    inline int ipPort() const { return _IpPort; }

    virtual QString toString();

protected:

    int _TargetUserName;
    int _TargetLogonId;
    int _LogonType;
    int _IpAddress;
    int _IpPort;
};

#endif // USERLOGEDINEVENT_H
