#ifndef USERLOGGEDINEVENTPARSER_H
#define USERLOGGEDINEVENTPARSER_H

#include "eventparser.h"

class UserLogedInEventParser : public EventParser
{
public:
    UserLogedInEventParser();

    virtual Event* parseEvent(QXmlStreamReader& xml);
};

#endif // USERLOGGEDINEVENTPARSER_H
