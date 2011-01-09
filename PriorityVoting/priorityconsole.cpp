#include "priorityconsole.h"

PriorityConsole::PriorityConsole()
{
}

void PriorityConsole::print(QList<QString> list)
{
    QTextStream output(stdout);
    for(int i=0; i<list.size(); i++) {
        output << list.at(i);
    }
    output << endl;
}

void PriorityConsole::print(QString str)
{
    QTextStream output(stdout);
    output << str;
    output << endl;
}
