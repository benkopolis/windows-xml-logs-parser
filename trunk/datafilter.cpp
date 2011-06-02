#include "datafilter.h"

DataFilter::DataFilter(QObject *parent) :
    QObject(parent)
{
}

QBuffer* DataFilter::filter(Configuration* c, QIODevice* device)
{
    return 0;
}
