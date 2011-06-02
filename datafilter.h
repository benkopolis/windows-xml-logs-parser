#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <QObject>
#include <QBuffer>
#include "configuration.h"

class DataFilter : public QObject
{
Q_OBJECT
public:
    explicit DataFilter(QObject *parent = 0);

signals:

public slots:

    QBuffer* filter(Configuration* c, QIODevice* device);

};

#endif // DATAFILTER_H
