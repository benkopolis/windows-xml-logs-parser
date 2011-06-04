#include <QtCore/QCoreApplication>
#include <QStringList>
#include "logparser.h"
#include <QFile>
#include <QDebug>
#include "datamapper.h"
#include "configuration.h"
#include "commons/exception.h"
#include <QElapsedTimer>

enum ExitCode
{
	GOOD = 0,
	INVALID_CONFIGURATION_FILE,
	INVALID_DATAMAPPER_FILE
};


void aboutConfig(QTextStream& out);
QString printException(Exception* e);
void printException(Exception* e, QTextStream& out);

void aboutConfig(QTextStream& out)
{
	out << "Invalid configuration !" << endl
		<< "Create new or fix the old one." << endl
		<< "Default configuration path is: ./configwxml.txt"
		<< endl << "Default content is:" << endl << endl
		<< "intlist:parsedevents:4625,4688,4689,4634,4624" << endl
		<< "string:inxml:input.xml" << endl
		<< "string:outfile:output.txt" << endl;
}

QString printException(Exception* e)
{
	QString o;
	QTextStream out(&o);
	printException(e, out);
	return o;
}

void printException(Exception* e, QTextStream& out)
{
	out << "Exception occured in " << e->file_name()
		<< " at line number " << e->line_number() << endl;
	out << "Exception message: " << endl
		<< e->message() << endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
	QElapsedTimer timer;
	QTextStream out(stdout);
	QFile f("C:\\Users\\zby\\Downloads\\0do255.xml");
	QFile of("C:\\Users\\zby\\Desktop\\test_wxlp2.txt");
	QFile dmfile("C:\\Users\\zby\\Desktop\\dmfile2.txt");
	QFile cfile("C:\\Users\\zby\\Desktop\\configwxml.txt");
	bool op = dmfile.open(QIODevice::ReadWrite | QIODevice::Text);
    if(!op)
		out << "Unable to open datamapper file - new one will be generated." << endl;
	Configuration *c = Configuration::instance();
	c->readConfig(&cfile);
	if(c->validateConfiguration() == false)
	{
		aboutConfig(out);
		return INVALID_CONFIGURATION_FILE;
	}
	try {
		LogParser lp;
		timer.start();
		DataMapper* dm = DataMapper::readDataMapper(&dmfile);
		qDebug() << "datamapper read time: " << (float)timer.elapsed()/1000.0;
		timer.restart();
		lp.parse(&f);
		qDebug() << "parse time: " << (float)timer.elapsed()/1000.0;
		lp.saveEvents(&of);
		dmfile.close();
		f.close(); of.close();
		cfile.close();
		dmfile.open(QIODevice::ReadWrite | QIODevice::Text);
		dm->saveDataMapper(&dmfile);
		qDebug() << "end";
	} catch (Exception* e) {
		printException(e, out);
		qDebug() << printException(e);
		int fe=0;
		fe = 10;
	}

	return GOOD;//a.exec();
}
