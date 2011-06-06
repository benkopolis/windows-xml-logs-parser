#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>
#include <QTextStream>
#include "../datamapper.h"

/**
  * Bazowa klasa dla wszystkich zdarzeñ. To w niej (w kontruktorze i)
  * w konstruktorach klas potomnych) wykonywane jest mapowanie.
  */
class Event
{

private:
	Event(int o, int s, int u);

public:
	Event();
	Event(const QString& o, const QString& s, const QString& u, const QString& t);

    inline uint occurenceTime() const { return _occurenceTime; }
    inline int sessionId() const { return _sessionId; }
    inline int userId() const { return _userId; }
    inline int eventType() const { return _eventType; }

	/**
	  * Ta metoda konwertuje informacje o zdarzeniu na
	  * postac mozliwa do odczytania przez komputer.
	  */
    virtual QString toString();

protected:

    uint _occurenceTime;
    int _sessionId;
    int _userId;
    int _eventType;
	
	QString _type;
};

#endif // EVENT_H
