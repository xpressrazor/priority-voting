#include <QtGui/QApplication>
#include "mainwindow.h"
#include "priorityutil.h"
#include <QTextStream>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    /*
    PriorityUtil priorityUtil;
    QTextStream out(stdout);
    out << QString::number(priorityUtil.randInt(1, 100)) << endl;
    */

    return a.exec();
}
