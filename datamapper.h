#ifndef DATAMAPPER_H
#define DATAMAPPER_H

#include <QObject>
#include <QHash>
#include <QIODevice>
#include <QPair>

uint qHash(const QPair<QString, QString>& p);

class DataMapper : public QObject
{
Q_OBJECT
public:

    // call only after calling readDataMapper
    static DataMapper* instance();

    //first call readDataMapper
    static DataMapper* readDataMapper(QIODevice *input);
    bool saveDataMapper(QIODevice* output);

	bool contains(const QString& value, const QString& type) const;
    bool contains(int id) const;
	int id(const QString& value, const QString& type);
	QString name(int id) const;
	QString type(int id) const;

signals:

public slots:

protected:

    explicit DataMapper(QObject *parent = 0);


	QHash<QPair<QString, QString>, int> _namesToIds;
	QHash<int, QPair<QString, QString> > _idsToNames;

    static int _nextId;

private:

    static DataMapper* _instance;
};

#endif // DATAMAPPER_H
