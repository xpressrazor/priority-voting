#include "voterdialog.h"
#include "ui_voterdialog.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QRegExp>

VoterDialog::VoterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoterDialog)
{
    // Let's show previous values from voters.txt if there were some
    ui->setupUi(this);
    QFile data("voters.txt");
    if(data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        QString line;
        do{
            line = in.readLine();
            ui->textEdit->append(line);

        }while(!line.isNull());
    }
}

QString VoterDialog::getVoters()
{
    return ui->textEdit->toPlainText();//.simplified();    // Remove possible white spaces
}

VoterDialog::~VoterDialog()
{
    delete ui;
}
