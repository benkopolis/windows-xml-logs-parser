#ifndef EVENTPARSER_H
#define EVENTPARSER_H

#include <QXmlStreamReader>
#include "../event/event.h"
#include <QDateTime>

/**
  * Bazowa klasa dla wszystkich klas analizuj�cych zdarzenia.
  * 4688 Zosta� stworzony proces.
  * 4689 Proces si� zako�czy�.
  * 4624 U�ytkownik si� zalogowa�.
  * 4625 U�ytkownikowi nie uda�o si� zalogowa�.
  * 4634 U�ytkownik si� wylogowa�.
  *
  */
class EventParser
{
public:

    inline int eventId() const { return _eventId; }

    virtual Event* parseEvent(QXmlStreamReader& xml) = 0;

protected:

    EventParser(int eventId);

private:
    EventParser();
//    EventParser(const EventParser& another);
//    EventParser& operator = (const EventParser& another);

    const int _eventId;
};

#endif // EVENTPARSER_H
