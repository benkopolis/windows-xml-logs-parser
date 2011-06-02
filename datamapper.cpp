#include "datamapper.h"
#include <QStringList>
#include <QTextStream>


uint qHash(const QPair<QString, QString>& p)
{
	return qHash(p.first) + qHash(p.second);
}


int DataMapper::_nextId = -1;
DataMapper* DataMapper::_instance = 0;


DataMapper::DataMapper(QObject *parent) :
    QObject(parent)
{
}

DataMapper* DataMapper::instance()
{
    return _instance;
}

DataMapper* DataMapper::readDataMapper(QIODevice *input)
{
    if(_instance)
		return _instance;
    if(!input->isOpen())
		if(!input->open(QIODevice::ReadOnly | QIODevice::Text))
		  return 0;
    _instance = new DataMapper();
    QString line;
    QString val;
    int id;
    int nid;
    QTextStream in(input);
    in >> nid;
    if(in.atEnd())
    {
		_nextId = 0;
		return _instance;
    }
    _nextId = nid;
    bool ok = true;
    while(in.atEnd() == false)
    {
		line = in.readLine();
		QStringList l = line.split(QChar(':'), QString::KeepEmptyParts);
		if(l.size() < 3)
			continue;
		id = l.at(1).toInt(&ok);
		if(!ok)
			continue;
		for(int i =2; i < l.size(); ++i)
		{
			val.append(l.at(i));
			val.append(":");
		}
		val = val.mid(0, val.length()-1);
		_instance->_idsToNames[id].second = val;
		_instance->_idsToNames[id].first = l.at(0);
		_instance->_namesToIds[_instance->_idsToNames[id]] = id;
		val.clear();
    }
	int chck1 = _instance->_namesToIds.size();
	int chck2 = _instance->_idsToNames.size();
    return _instance;
}

bool DataMapper::saveDataMapper(QIODevice* output)
{
    if(!output->isOpen())
		if(!output->open(QIODevice::WriteOnly | QIODevice::Text))
		  return false;
    QTextStream out(output);
    out << _nextId << endl;
    foreach(int i, _idsToNames.keys())
    {
		out << _idsToNames[i].first << ":" << i << ":"
				<< _idsToNames[i].second << endl;
    }
    return true;
}

bool DataMapper::contains(const QString& value, const QString& type) const
{
	QPair<QString, QString> p(type, value);
	return _namesToIds.contains(p);
}

bool DataMapper::contains(int id) const
{
    return _idsToNames.contains(id);
}

int DataMapper::id(const QString& value, const QString& type)
{
	if(type.isEmpty() == true)
	{
		int t =0;
		t++;
		Q_ASSERT(false);
	}
	QPair<QString, QString> p(type, value);
	if(_namesToIds.contains(p))
		return _namesToIds[p];
	_namesToIds[p] = _nextId;
	_idsToNames[_nextId].second = value;
	_idsToNames[_nextId].first = type;
    ++_nextId;
    return _nextId-1;
}

QString DataMapper::name(int id) const
{
    if(_idsToNames.contains(id))
		return _idsToNames[id].second;
    return QString();
}

QString DataMapper::type(int id) const
{
	if(_idsToNames.contains(id))
		return _idsToNames[id].first;
	return QString();
}
