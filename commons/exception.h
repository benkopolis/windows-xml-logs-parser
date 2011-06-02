#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class Exception
{
public:
    Exception();
    Exception(const QString& msg);
    Exception(const QString& msg, const QString& file);
    Exception(const QString& msg, const QString& file, int line);

    inline QString message() const { return m_message; }
    inline QString file_name() const { return m_file; }
    inline int line_number() const { return m_line; }

protected:

    QString m_message;
    QString m_file;
    int m_line;
};

#endif // EXCEPTION_H
