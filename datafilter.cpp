#include "datafilter.h"

DataFilter::DataFilter(QObject *parent) :
    QObject(parent)
{
}

DataFilter::DataFilter(Configuration* c, QObject *parent) :
	QObject(parent)
{
	this->initialize(c);
}

void DataFilter::initialize()
{
	this->initialize(Configuration::instance());
}

void DataFilter::initialize(Configuration* c)
{
	QString older("eventsolderthen"), younger("eventsyoungerthen");
	QString fa("filterattribs"), fav("filterav");
	QVariantMap props = c->properties();
	QDateTime dt, bdt;
	bdt = QDateTime::fromString("2000-01-01T00:00:00", Qt::ISODate);
	if(props.contains(older))
	{
		dt = QDateTime::fromString(props[older].toString(), Qt::ISODate);
		this->_olderThen = dt.toTime_t() - bdt.toTime_t();
	}
	else
		this->_olderThen = 0;
	if(props.contains(younger))
	{
		dt = QDateTime::fromString(props[younger].toString(), Qt::ISODate);
		this->_youngerThen = dt.toTime_t() - bdt.toTime_t();
	}
	else
		this->_youngerThen = -1;
	if(props.contains(fa))
	{
		this->_attribs = props[fa].toString().split(',');
	}
	if(props.contains(fav))
	{
		QStringList ll = props[fav].toString().split(',');
		foreach(QString elem, ll)
		{
			QStringList tmp = elem.split(':');
			QString val;
			for(int i=1; i<tmp.size(); ++i)
			{
				val = val.append(tmp.at(i));
				val = val.append(':');
			}
			val = val.mid(0, val.length()-1);
			this->_attribsAndValues.insert(tmp.at(0), val);
		}
	}
}

