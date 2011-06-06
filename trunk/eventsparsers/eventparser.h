#ifndef EVENTPARSER_H
#define EVENTPARSER_H

#include <QXmlStreamReader>
#include "../event/event.h"
#include <QDateTime>
#include <QVariantList>
#include <QVariantMap>
#include "../datafilter.h"

/**
  * Bazowa klasa dla wszystkich klas analizuj¹cych zdarzenia.
  * 4688 Zosta³ stworzony proces.
  * 4689 Proces siê zakoñczy³.
  * 4624 U¿ytkownik siê zalogowa³.
  * 4625 U¿ytkownikowi nie uda³o siê zalogowaæ.
  * 4634 U¿ytkownik siê wylogowa³.
  *
  */
class EventParser
{
public:

    inline int eventId() const { return _eventId; }

	/**
	  * Ta metoda jest w ka¿dej klasie bardzo podobna.
	  * Dla lokalnej czytelnoœci nie zosta³a sparametryzowana.
	  * ¯eby zaimplementowaæ nowego parsera wystarczy j¹ skopiowaæ
	  * i podmieniæ nazwy szukanych atrybutów oraz tworzone i zwracane zdarzenia.
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
