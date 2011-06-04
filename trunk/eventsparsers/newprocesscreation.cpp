#include "newprocesscreation.h"
#include "../event/newprocesscreationevent.h"
#include "../datafilter.h"

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
	QDateTime dt, bdt;
	bdt = QDateTime::fromString("2000-01-01T00:00:00", Qt::ISODate);
    while(xml.atEnd() == false)
    {
		readed = xml.readNext();
		if(xml.name().compare("TimeCreated", Qt::CaseSensitive) == 0 && readed == QXmlStreamReader::StartElement)
		{
			tmp = xml.readElementText(QXmlStreamReader::SkipChildElements);
			time = tmp.mid(0, 19);
			dt = QDateTime::fromString(time, Qt::ISODate);
			uint otime = dt.toTime_t() - bdt.toTime_t();
			if(_filter->youngerThen() < otime && _filter->youngerThen() != -1)
				return 0;
			if(_filter->olderThen() > otime && _filter->olderThen() != 0)
				return 0;
		}
		else if(xml.name().compare("Data", Qt::CaseSensitive) == 0 && readed == QXmlStreamReader::StartElement)
		{
			attribs = xml.attributes();
			if(attribs.hasAttribute("", "Name"))
			{
				tmp = attribs.value("Name").toString();
				QString val = xml.readElementText(QXmlStreamReader::SkipChildElements);
				if(_filter->attribs().contains(tmp))
					return 0;
				if(_filter->attribsAndValues().contains(tmp) &&
						_filter->attribsAndValues().values(tmp).contains(val))
					return 0;
				if(QString::compare(tmp, "SubjectUserName")==0)
					user = val;
				if(QString::compare(tmp, "SubjectLogonId")==0)
					session = val;
				if(QString::compare(tmp, "NewProcessId")==0)
					npid = val;
				if(QString::compare(tmp, "NewProcessName")==0)
					npname = val;
				if(QString::compare(tmp, "ProcessId")==0)
					pid = val;
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
