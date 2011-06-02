#include <QtCore/QCoreApplication>
#include <QStringList>
#include "logparser.h"
#include <QFile>
#include <QDebug>
#include "datamapper.h"
#include "configuration.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
    QFile f("C:\\Users\\zby\\Downloads\\0do255.xml");
    QFile of("C:\\Users\\zby\\Desktop\\test_wxlp.txt");
    QFile dmfile("C:\\Users\\zby\\Desktop\\dmfile.txt");
    bool op = f.open(QIODevice::Text | QIODevice::ReadOnly) &&
	      dmfile.open(QIODevice::ReadWrite | QIODevice::Text);
    if(!op)
    {
	qDebug() << "unable to open";
	return 0;
    }
    LogParser lp;
    DataMapper* dm = DataMapper::readDataMapper(&dmfile);
    qDebug() << "before parse";
    lp.parse(&f);
    qDebug() << "before save";
    lp.saveEvents(&of);
    dmfile.close();
    f.close(); of.close();
	dmfile.open(QIODevice::ReadWrite | QIODevice::Text);
    dm->saveDataMapper(&dmfile);
    qDebug() << "end";
    return 0;//a.exec();
}
