#ifndef LOGINFAILEDEVENT_H
#define LOGINFAILEDEVENT_H

#include "event.h"

class LoginFailedEvent : public Event
{
protected:
    LoginFailedEvent();

public:
	LoginFailedEvent(const QString& time, const QString& session, const QString& user);

protected:



};

#endif // LOGINFAILEDEVENT_H
