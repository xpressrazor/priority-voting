#include "catagorydialog.h"
#include "ui_catagorydialog.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QList>
#include "priorityfile.h"

CatagoryDialog::CatagoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatagoryDialog)
{
    // Let's show previous values from catagories.txt if there were some
    ui->setupUi(this);
    QList<QString> list = PriorityFile::readFile("catagories.txt");
    QString formattedText;
    for(int i=0; i<list.size(); i++) {
        formattedText.append(list.at(i));
    }
    ui->textEdit->append(formattedText);

    /*
    QFile data("catagories.txt");
    if(data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        QString line;
        do{
            line = in.readLine();
            ui->textEdit->append(line);

        }while(!line.isNull());
    }*/
}

QString CatagoryDialog::getCatagories()
{
    return ui->textEdit->toPlainText();
}

CatagoryDialog::~CatagoryDialog()
{
    delete ui;
}
