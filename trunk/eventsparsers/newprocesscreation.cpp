#include "newprocesscreation.h"
#include "../event/newprocesscreationevent.h"

NewProcessCreationEventParser::NewProcessCreationEventParser():
    EventParser(4688)
{
}

Event* NewProcessCreationEventParser::parseEvent(QXmlStreamReader& xml)
{
    QString tmp;
    QXmlStreamReader::TokenType readed;
    QXmlStreamAttributes attribs;
    QString user, session, time, pid, npname, npid;
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
		if(QString::compare(tmp, "NewProcessId")==0)
		    npid = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "NewProcessName")==0)
		    npname = xml.readElementText(QXmlStreamReader::SkipChildElements);
		if(QString::compare(tmp, "ProcessId")==0)
		    pid = xml.readElementText(QXmlStreamReader::SkipChildElements);
	    }
	}
	else if(xml.name().compare("Event", Qt::CaseSensitive) == 0 && readed == QXmlStreamReader::EndElement)
	    break;
    }
    if(xml.hasError())
	return 0;
    NewProcessCreationEvent* e = new NewProcessCreationEvent(time, session, user, npid, pid, npname);
    return e;
}
