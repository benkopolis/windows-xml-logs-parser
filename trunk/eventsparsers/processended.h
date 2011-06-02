#ifndef PROCESSENDEDEVENTPARSER_H
#define PROCESSENDEDEVENTPARSER_H

#include "eventparser.h"

class ProcessEndedEventParser : public EventParser
{
public:
    ProcessEndedEventParser();

    virtual Event* parseEvent(QXmlStreamReader& xml);
};

#endif // PROCESSENDEDEVENTPARSER_H
