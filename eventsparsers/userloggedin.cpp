#include "userloggedin.h"
#include "../event/userlogedinevent.h"

UserLogedInEventParser::UserLogedInEventParser():
    EventParser(4624)
{
}

Event* UserLogedInEventParser::parseEvent(QXmlStreamReader& xml)
{
    QString tmp;
    QXmlStreamReader::TokenType readed;
    QXmlStreamAttributes attribs;
    QString sun, ss, time, tun, tss, lt, ip, ia;
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
		    sun = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "SubjectLogonId")==0)
		    ss = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "TargetUserName")==0)
		    tun = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "TargetLogonId")==0)
		    tss = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "LogonType")==0)
		    lt = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "IpAddress")==0)
		    ia = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "IpPort")==0)
		    ip = xml.readElementText(QXmlStreamReader::SkipChildElements);
	    }
	}
	else if(xml.name().compare("Event", Qt::CaseSensitive) == 0 && readed == QXmlStreamReader::EndElement)
	    break;
    }
    if(xml.hasError())
	return 0;
    UserLogedInEvent* e = new UserLogedInEvent(time, ss, sun, tun, tss, lt, ia, ip);
    return e;
}
