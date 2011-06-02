#ifndef USERLOGEDOUTEVENTPARSER_H
#define USERLOGEDOUTEVENTPARSER_H

#include "eventparser.h"

class UserLogedOutEventParser : public EventParser
{
public:
    UserLogedOutEventParser();

    virtual Event* parseEvent(QXmlStreamReader& xml);
};

#endif // USERLOGEDOUTEVENTPARSER_H
