#ifndef PRIORITYCONSOLE_H
#define PRIORITYCONSOLE_H

#include <QList>
#include <QString>
#include <QTextStream>

class PriorityConsole
{
public:
    PriorityConsole();
    static void print(QList<QString> list);
    static void print(QString str);
};

#endif // PRIORITYCONSOLE_H
