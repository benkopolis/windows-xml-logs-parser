#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QIODevice>
#include <QVariantMap>
#include "commons/exception.h"
#include <QMutex>

/**
  * This class reads configuration from given file.
  * Coniguration should have proper format, described in documentation.
  * It is singleton protected by MUTEX.
  */
class Configuration : public QObject
{
Q_OBJECT
public:

    static Configuration* instance();

	bool validateConfiguration() const;

	inline QVariantMap& properties() { return m_properties; }

signals:

public slots:

    void readConfig(QIODevice* device);
    void saveConfig(QIODevice* device);

protected:

    QVariantMap m_properties;
    static Configuration* m_instance;
    static QMutex* m_mutex;

    void readSingleLine(QString line);

    explicit Configuration(QObject *parent = 0);

};

#endif // CONFIGURATION_H
