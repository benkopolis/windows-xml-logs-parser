#include "configuration.h"
#include <QTextStream>
#include <QStringList>
#include <QVariantList>
#include <QVariant>


Configuration* Configuration::m_instance = new Configuration();
QMutex* Configuration::m_mutex = new QMutex();


Configuration* Configuration::instance()
{
    m_mutex->lock();
    if(m_instance == 0)
	m_instance = new Configuration();
    m_mutex->unlock();
    return m_instance;
}

Configuration::Configuration(QObject *parent) :
    QObject(parent)
{
}

void Configuration::readConfig(QIODevice* device)
{
    if(!device->isOpen())
	if(!device->open(QIODevice::ReadOnly | QIODevice::Text))
	    throw new Exception("Cannot open configuration file.", __FILE__, __LINE__);
    QTextStream in(device);
    if(in.device()->isOpen() == false)
	throw new Exception("Cannot open configuration file.", __FILE__, __LINE__);
    while(in.atEnd() == false)
	this->readSingleLine(in.readLine());
}

void Configuration::saveConfig(QIODevice* device)
{
    if(!device->isOpen())
	if(!device->open(QIODevice::WriteOnly | QIODevice::Text))
	    throw new Exception("Cannot open configuration file.", __FILE__, __LINE__);
    QTextStream out(device);
    foreach(QString name, this->m_properties.keys())
    {
	if(m_properties[name].canConvert(QVariant::List))
	{
	    QVariantList tmpl = m_properties[name].toList();
	    QStringList strtmpl = m_properties[name].toStringList();
	    if(strtmpl.isEmpty())
		out << "intlist:" << name << ":";
	    else
		out << "stringlist:" << name << ":";
	    foreach(QVariant v, tmpl)
	    {
		if(strtmpl.isEmpty())
		    out << v.toInt() << ",";
		else
		    out << v.toString() << ",";
	    }
	    out << endl;
	}
	else if(m_properties[name].canConvert(QVariant::Int))
	{
	    out << "int:" << name << ":" << m_properties[name].toInt();
	}
	else if(m_properties[name].canConvert(QVariant::String))
	{
	    out << "string:" << name << ":" << m_properties[name].toString() << endl;
	}
    }
}

void Configuration::readSingleLine(QString line)
{
    if(line.startsWith(QChar('#')))
	return;
    QStringList elems = line.split(QChar(':'));
    if(elems.size() != 3)
	return;
    QString type = elems.at(0);
    QString name = elems.at(1);
    QString value = elems.at(2);
    bool ok = true;
    if(QString::compare(type, "int") == 0)
    {
	int tmp = value.toInt(&ok);
	if(ok == true)
	    this->m_properties[name] = tmp;
    }
    else if(QString::compare(type, "string") == 0)
    {
	this->m_properties[name] = value;
    }
    else if(QString::compare(type, "intlist") == 0)
    {
	QStringList value_list = value.split(QChar(','));
	int tmp = 0;
	QVariantList values;
	foreach(QString val, value_list)
	{
	    tmp = val.toInt(&ok);
	    if(ok)
		values.push_back(tmp);
	}
	this->m_properties[name] = values;
    }
    else if(QString::compare(type, "stringlist") == 0)
    {
	QStringList value_list = value.split(QChar(','));
	QVariantList values;
	foreach(QString val, value_list)
	{
	    values.push_back(val);
	}
	this->m_properties[name] = values;
    }
}
