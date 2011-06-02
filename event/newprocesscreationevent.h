#ifndef NEWPROCESSCREATIONEVENT_H
#define NEWPROCESSCREATIONEVENT_H

#include "event.h"

class NewProcessCreationEvent : public Event
{
public:
    NewProcessCreationEvent(const QString& time, const QString& session, const QString& user,
			    const QString& newProcess, const QString& oldProcess,
			    const QString& newProcessName);

    inline int newProcessId() const { return _NewProcessId; }
    inline int processId() const { return _ProcessId; }
    inline int newProcessName() const { return _NewProcessName; }

    virtual QString toString();

protected:
    NewProcessCreationEvent();

    int _NewProcessId;
    int _ProcessId;
    int _NewProcessName;
};

#endif // NEWPROCESSCREATIONEVENT_H
