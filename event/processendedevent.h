#ifndef PROCESSENDEDEVENT_H
#define PROCESSENDEDEVENT_H

#include "event.h"

class ProcessEndedEvent : public Event
{
public:
    ProcessEndedEvent(const QString& time, const QString& session, const QString& user,
		     const QString& process, const QString& status,
		     const QString& processName);

    inline int processId() const { return _ProcessId; }
    inline int processName() const { return _ProcessName; }
    inline int processStatus() const { return _Status; }

    virtual QString toString();

protected:
    ProcessEndedEvent();

    int _ProcessId;
    int _ProcessName;
    int _Status;
};

#endif // PROCESSENDEDEVENT_H
