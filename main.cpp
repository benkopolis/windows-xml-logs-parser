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

enum Arguments
{
	U_ARG =0,
	C_ARG,
	I_ARG,
	O_ARG,
	M_ARG,
	H_ARG
};

const int MY_ARGS_LEN = 6;

void aboutConfig(QTextStream& out);
void aboutCmd(QTextStream& out);
QString printException(Exception* e);
void printException(Exception* e, QTextStream& out);
void parseCmd(QTextStream& out, QStringList& args, QElapsedTimer& timer);

void aboutConfig(QTextStream& out)
{
	out << "Invalid configuration !" << endl
		<< "Create new or fix the old one." << endl
		<< "Default configuration path is: configwxml.txt"
		<< endl << "Default content is:" << endl << endl
		<< "intlist:parsedevents:4625,4688,4689,4634,4624" << endl
		<< "string:inxml:input.xml" << endl
		<< "string:outfile:output.txt" << endl
		<< "string:dmfile:dmfile.txt" << endl;
}

void aboutCmd(QTextStream& out)
{
	out << "No parameters - program reads default configuration file (configwxml.txt)" << endl
		<< "-u <int>\t\tunmapps given id" << endl
		<< "-c <file_path\t\treads configuration from given path" << endl
		<< "-i <file_path>\t\toverrides inxml option in configuration" << endl
		<< "-o <file_path>\t\toverrides outfile option in configuration" << endl
		<< "-m <file_path>\t\toverrides dmfile option in configuration" << endl
		<< "-h\t\tprints this message." << endl;
	out << "-u and -c and -m are allowed together in any configuration;" << endl
		<< "-u is not allowed with -i and -o;" << endl
		<< "-c, -i, -o and -m are allowed together in any configuration" << endl;
	out << endl << "-h have the highest priority, second is -u ." << endl;
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

void parseCmd(QTextStream& out, QStringList& args, QElapsedTimer& timer)
{
	int args_position[6] = {
		args.indexOf("-u"),
		args.indexOf("-c"),
		args.indexOf("-i"),
		args.indexOf("-o"),
		args.indexOf("-m"),
		args.indexOf("-h")};
	if(args_position[H_ARG] != -1) // help
	{
		aboutCmd(out);
		return;
	}
	else if(args_position[U_ARG] != -1) // unmap
	{
		if(args.size() < 3 ||
				(args_position[C_ARG] != -1 && args.size() < 5) ||
				(args_position[M_ARG] != -1 && args.size() < 5) ||
				((args_position[C_ARG] + args_position[M_ARG]) != -2 && args.size() < 7) ||
				(abs(args_position[C_ARG] - args_position[M_ARG]) == 2) ||
				(abs(args_position[C_ARG] - args_position[U_ARG]) == 2) ||
				(abs(args_position[U_ARG] - args_position[M_ARG]) == 2) ||)
		{
			aboutCmd(out);
			return;
		}
		bool parse_ok = true;
		int in_id = args.at(args_position[U_ARG]+1).toInt(&parse_ok);
		if(!parse_ok)
		{
			aboutCmd(out);
			return;
		}
		QString c_file;
		if(args_position[C_ARG] != -1)
			c_file = args.at(args_position[C_ARG]+1);
		else
			c_file = "configwxml.txt";
		QFile cfg_file(c_file);
		Configuration *c = Configuration::instance();
		c->readConfig(&cfile);
		if(c->validateConfiguration() == false)
		{
			aboutConfig(out);
			return INVALID_CONFIGURATION_FILE;
		}
		if(args_position[M_ARG] != -1)
			c_file = args.at(args_position[M_ARG]+1);
		else
			c_file = c->properties().value("dmfile");
		QFile dmfile(c_file);
		DataMapper* dm = DataMapper::readDataMapper(&dmfile);
		out << dm->type(in_id) << ':' << in_id << ':' << dm->name(in_id) << endl;
	}									// finish unmap
	else								// parse logs
	{

	}									// finish parse logs
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
	QElapsedTimer timer;
	QTextStream out(stdout);
	if(args.size() == 1)
	{
		QFile cfile("configwxml.txt");
		Configuration *c = Configuration::instance();
		c->readConfig(&cfile);
		if(c->validateConfiguration() == false)
		{
			aboutConfig(out);
			return INVALID_CONFIGURATION_FILE;
		}

		QFile f(c->properties().value("inxml"));
		QFile of(c->properties().value("outfile"));
		QFile dmfile(c->properties().value("dmfile"));
		bool op = dmfile.open(QIODevice::ReadWrite | QIODevice::Text);
		if(!op)
			out << "Unable to open datamapper file - new one will be generated." << endl;
		try {
			LogParser lp;
			timer.start();
			DataMapper* dm = DataMapper::readDataMapper(&dmfile);
			qDebug() << "datamapper read time: " << (float)timer.elapsed()/1000.0 << 's';
			timer.restart();
			lp.parse(&f);
			qDebug() << "parse time: " << (float)timer.elapsed()/1000.0 << 's';
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
	}
	else
	{ // parse cmd
		parseCmd(out, args, timer);
	}
	return GOOD;//a.exec();
}
