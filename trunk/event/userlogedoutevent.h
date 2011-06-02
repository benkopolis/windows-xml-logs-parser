#ifndef USERLOGEDOUTEVENT_H
#define USERLOGEDOUTEVENT_H

#include "event.h"

class UserLogedOutEvent : public Event
{
public:

    UserLogedOutEvent(const QString& time, const QString& session, const QString& user,
		     const QString& targetUser,
		     const QString& targetSession);

protected:
    UserLogedOutEvent();

public:

    inline int targetUserName() const { return _TargetUserName; }
    inline int targetLogonId() const { return _TargetLogonId; }

    virtual QString toString();

protected:

    int _TargetUserName;
    int _TargetLogonId;
};

#endif // USERLOGEDOUTEVENT_H
