#ifndef PRIORITYFILE_H
#define PRIORITYFILE_H

#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>

class PriorityFile
{
public :
    PriorityFile();
    static QList<QString> readFile(QString fileName);
    static bool writeToFile(QList<QString> lines, QString fileName);
    static bool writeToFile(QString line, QString fileName);
    static bool appendToFile(QString line, QString fileName);
    static bool clearFile(QString fileName);
};

#endif // PRIORITYFILE_H
