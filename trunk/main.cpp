#include <QtCore/QCoreApplication>
#include <QStringList>
#include "logparser.h"
#include <QFile>
#include <QFileInfo>
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
Configuration* createConfiguration(int configPos, QStringList& args);
DataMapper* createDataMapper(int dmPos, QStringList& args, Configuration* c);
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

Configuration* createConfiguration(int configPos, QStringList& args, QTextStream& out)
{
	QFileInfo n(args.at(0));
	QString c_file = n.path();
	if(configPos != -1)
		c_file = args.at(configPos+1);
	else
		c_file = c_file.append("/configwxml.txt");
	QFile cfg_file(c_file);
	Configuration *c = Configuration::instance();
	c->readConfig(&cfg_file);
	if(c->validateConfiguration() == false)
	{
		aboutConfig(out);
		throw new Exception("Invalid configuration file.", __FILE__, __LINE__);
	}
	cfg_file.close();
	return c;
}

DataMapper* createDataMapper(int dmPos, QStringList& args, Configuration* c)
{
	QString c_file;
	if(dmPos != -1)
		c_file = args.at(dmPos+1);
	else
		c_file = c->properties().value("dmfile").toString();
	QFile dmfile(c_file);
	DataMapper* dm = DataMapper::readDataMapper(&dmfile);
	dmfile.close();
	return dm;
}

void saveDataMapper(int dmPos, QStringList& args, Configuration* c, DataMapper* dm)
{
	QString c_file;
	if(dmPos != -1)
		c_file = args.at(dmPos+1);
	else
		c_file = c->properties().value("dmfile").toString();
	QFile dmfile(c_file);
	dm->saveDataMapper(&dmfile);
	dmfile.close();
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
				(abs(abs(args_position[C_ARG]) - abs(args_position[M_ARG])) == 1) ||
				(abs(abs(args_position[C_ARG]) - abs(args_position[U_ARG])) == 1) ||
				(abs(abs(args_position[U_ARG]) - abs(args_position[M_ARG])) == 1))
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
		Configuration *c = createConfiguration(args_position[C_ARG], args, out);
		DataMapper* dm = createDataMapper(args_position[M_ARG], args, c);
		out << dm->type(in_id) << ':' << in_id << ':' << dm->name(in_id) << endl;
		delete c;
		delete dm;
	}									// finish unmap
	else								// parse logs
	{
		int enabled = 0;
		for(int i=0; i< MY_ARGS_LEN; ++i)
			enabled += args_position[i] != -1 ? 1 : 0;
		int max_enabled = 4;
		int min_size = 1+2*(enabled > max_enabled ? max_enabled : enabled);
		if(args.size() < min_size ||
				(abs(abs(args_position[C_ARG]) - abs(args_position[M_ARG])) == 1) ||
				(abs(abs(args_position[C_ARG]) - abs(args_position[I_ARG])) == 1) ||
				(abs(abs(args_position[C_ARG]) - abs(args_position[O_ARG])) == 1) ||
				(abs(abs(args_position[I_ARG]) - abs(args_position[O_ARG])) == 1) ||
				(abs(abs(args_position[M_ARG]) - abs(args_position[O_ARG])) == 1) ||
				(abs(abs(args_position[M_ARG]) - abs(args_position[I_ARG])) == 1))
		{
			aboutCmd(out);
			return;
		}
		QString c_file;
		Configuration *c = createConfiguration(args_position[C_ARG], args, out);
		DataMapper* dm = createDataMapper(args_position[M_ARG], args, c);
		LogParser lp;
		if(args_position[I_ARG] != -1)
			c_file = args.at(args_position[I_ARG]+1);
		else
			c_file = c->properties().value("inxml").toString();
		QFile xml_file(c_file);
		lp.parse(&xml_file);
		qDebug() << "parsing done.";
		if(args_position[O_ARG] != -1)
			c_file = args.at(args_position[O_ARG]+1);
		else
			c_file = c->properties().value("outfile").toString();
		QFile o_file(c_file);
		lp.saveEvents(&o_file);
		qDebug() << "saving logs done.";
		saveDataMapper(args_position[M_ARG], args, c, dm);
		qDebug() << "saving data mapping done.";
		delete dm;
		delete c;
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
		QString cfg_path = a.applicationDirPath().append("/configwxml.txt");
		QFile cfile(cfg_path);
		Configuration *c = Configuration::instance();
		try {
			c->readConfig(&cfile);
			if(c->validateConfiguration() == false)
			{
				aboutConfig(out);
				return INVALID_CONFIGURATION_FILE;
			}

			QFile f(c->properties().value("inxml").toString());
			QFile of(c->properties().value("outfile").toString());
			QFile dmfile(c->properties().value("dmfile").toString());
			bool op = dmfile.open(QIODevice::ReadWrite | QIODevice::Text);
			if(!op)
				out << "Unable to open datamapper file - new one will be generated." << endl;
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
			dmfile.close();
			qDebug() << "end";
			delete dm;
			delete c;
	} catch (Exception* e) {
		printException(e, out);
		qDebug() << printException(e);
	}
	}
	else
	{ // parse cmd
		try
		{
			parseCmd(out, args, timer);
		}
		catch(Exception* e)
		{
			printException(e, out);
			qDebug() << printException(e);
		}
	}
	return GOOD;//a.exec();
}
