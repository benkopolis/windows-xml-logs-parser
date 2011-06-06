#ifndef EVENTPARSER_H
#define EVENTPARSER_H

#include <QXmlStreamReader>
#include "../event/event.h"
#include <QDateTime>
#include <QVariantList>
#include <QVariantMap>
#include "../datafilter.h"

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

	/**
	  * Ta metoda jest w ka�dej klasie bardzo podobna.
	  * Dla lokalnej czytelno�ci nie zosta�a sparametryzowana.
	  * �eby zaimplementowa� nowego parsera wystarczy j� skopiowa�
	  * i podmieni� nazwy szukanych atrybut�w oraz tworzone i zwracane zdarzenia.
	  */
    virtual Event* parseEvent(QXmlStreamReader& xml) = 0;

protected:

    EventParser(int eventId);

	DataFilter * _filter;

private:
    EventParser();
//    EventParser(const EventParser& another);
//    EventParser& operator = (const EventParser& another);

    const int _eventId;
};

#endif // EVENTPARSER_H
