#include "processended.h"
#include "../event/processendedevent.h"

ProcessEndedEventParser::ProcessEndedEventParser():
	EventParser(4689)
{
}

Event* ProcessEndedEventParser::parseEvent(QXmlStreamReader& xml)
{
    QString tmp;
    QXmlStreamReader::TokenType readed;
    QXmlStreamAttributes attribs;
    QString user, session, time, pid, pname, pstatus;
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
		    user = xml.readElementText();
		if(QString::compare(tmp, "SubjectLogonId")==0)
		    session = xml.readElementText();
		if(QString::compare(tmp, "ProcessId")==0)
		    pid = xml.readElementText();
		if(QString::compare(tmp, "ProcessName")==0)
		    pname = xml.readElementText();
		if(QString::compare(tmp, "Status")==0)
		    pstatus = xml.readElementText();
	    }
	}
	else if(xml.name().compare("Event", Qt::CaseSensitive) == 0 && readed == QXmlStreamReader::EndElement)
	    break;
    }
    if(xml.hasError())
	return 0;
    ProcessEndedEvent* e = new ProcessEndedEvent(time, session, user, pid, pstatus, pname);
    return e;
}
