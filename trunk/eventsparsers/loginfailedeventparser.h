#ifndef LOGINFAILEDEVENTPARSER_H
#define LOGINFAILEDEVENTPARSER_H

#include "eventparser.h"

class LogInFailedEventParser : public EventParser
{
public:
    LogInFailedEventParser();

    virtual Event* parseEvent(QXmlStreamReader& xml);
};

#endif // LOGINFAILEDEVENTPARSER_H
