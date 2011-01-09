#include "priorityfile.h"

PriorityFile::PriorityFile()
{
}

QList<QString> PriorityFile::readFile(QString fileName)
{
    QFile file(fileName);
    QTextStream inputStream(&file);
    QList<QString> list;

    if(file.open(QFile::ReadOnly)) {
        QString line;
        do {
            line = inputStream.readLine();
            if(line!="")    /* Is it a good idea to omit blank lines. I don't know */
                list.append(line);
        }while(!line.isNull());
    }

    file.close();
    return list;
}

/* We have appended endl so be careful if you don't need that */
bool PriorityFile::writeToFile(QList<QString> lines, QString fileName)
{
    QFile file(fileName);
    QTextStream outputStream(&file);

    if(file.open(QFile::WriteOnly)) {
        for(int i=0; i<lines.size(); i++) {
            outputStream << lines.at(i);
            outputStream << endl; /* If you have other plans for endl omit this line */
        }

        file.close();
        return true;
    }
    return false;
}

bool PriorityFile::writeToFile(QString line, QString fileName)
{
    QFile file(fileName);
    QTextStream outputStream(&file);

    if(file.open(QFile::WriteOnly)) {
        outputStream << line;

        file.close();
        return true;
    }
    return false;
}

bool PriorityFile::appendToFile(QString line, QString fileName)
{
    QFile file(fileName);
    QTextStream outputStream(&file);

    if(file.open(QFile::Append)) {
        outputStream << line;
        outputStream << endl; /* Each line ends with endl */

        file.close();
        return true;
    }
    return false;
}

bool PriorityFile::clearFile(QString fileName)
{
    QFile file(fileName);
    QTextStream outputStream(&file);

    if(file.open(QFile::WriteOnly)) {
       outputStream << "";

       file.close();
       return true;
    }
    return false;
}
