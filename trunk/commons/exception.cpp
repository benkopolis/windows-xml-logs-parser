#include "exception.h"

Exception::Exception()
{
}

Exception::Exception(const QString& msg):
    m_message(msg)
{

}

Exception::Exception(const QString& msg, const QString& file):
    m_message(msg),
    m_file(file)
{

}

Exception::Exception(const QString& msg, const QString& file, int line):
    m_message(msg),
    m_file(file),
    m_line(line)
{

}
