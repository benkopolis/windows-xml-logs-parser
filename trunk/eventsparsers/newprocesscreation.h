#ifndef NEWPROCESSCREATIONEVENTPARSER_H
#define NEWPROCESSCREATIONEVENTPARSER_H

#include "eventparser.h"

class NewProcessCreationEventParser : public EventParser
{
public:
    NewProcessCreationEventParser();

    virtual Event* parseEvent(QXmlStreamReader& xml);
};

#endif // NEWPROCESSCREATIONEVENTPARSER_H
