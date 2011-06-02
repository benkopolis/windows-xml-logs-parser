#include "userlogedouteventparser.h"
#include "../event/userlogedoutevent.h"

UserLogedOutEventParser::UserLogedOutEventParser():
    EventParser(4634)
{
}

Event* UserLogedOutEventParser::parseEvent(QXmlStreamReader& xml)
{
    QString tmp;
    QXmlStreamReader::TokenType readed;
    QXmlStreamAttributes attribs;
    QString user, session, time, tuser, tsession;
    while(xml.atEnd() == false)
    {
	readed = xml.readNext();
	if(xml.name().compare("TimeCreated", Qt::CaseSensitive) == 0 && readed == QXmlStreamReader::StartElement)
	{
	    tmp = xml.readElementText(QXmlStreamReader::SkipChildElements);
	    time = tmp.mid(0, 19);
	}
	else if(xml.name().compare("Data", Qt::CaseSensitive) == 0 && readed == QXmlStreamReader::StartElement)
	{
	    attribs = xml.attributes();
	    if(attribs.hasAttribute("", "Name"))
	    {
		tmp = attribs.value("Name").toString();
		if(QString::compare(tmp, "SubjectUserName")==0)
		    user = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "SubjectLogonId")==0)
		    session = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "TargetUserName")==0)
		    tuser = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "TargetLogonId")==0)
		    tsession = xml.readElementText(QXmlStreamReader::SkipChildElements);
	    }
	}
	else if(xml.name().compare("Event", Qt::CaseSensitive) == 0 && readed == QXmlStreamReader::EndElement)
	    break;
    }
    if(xml.hasError())
	return 0;
    UserLogedOutEvent* e = new UserLogedOutEvent(time, session, user, tuser, tsession);
    return e;
}
