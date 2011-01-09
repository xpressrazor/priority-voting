#include "votedialog.h"
#include "ui_votedialog.h"
#include <QFile>
#include <QTextStream>
#include <QComboBox>
#include <QVBoxLayout>

VoteDialog::VoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoteDialog)
{
    ui->setupUi(this);
    QFile data("catagories.txt");
    QTextStream inputStream(&data);
    QString line;
    QStringList list;
    QVBoxLayout *layout = new QVBoxLayout;


    if(data.open(QFile::ReadOnly)) {
        do {
            line = inputStream.readLine();
            QStringList splitted = line.split(":");

            if(splitted.size() > 1)
                list.append(splitted[1]);

        }while(!line.isNull());
    }

    QFile users("voters.txt");
    QTextStream votersStream(&users);
    QString votersLine;
    QStringList votersList;

    if(users.open(QFile::ReadOnly)) {
        do {
            votersLine = votersStream.readLine();
            QStringList splitted = votersLine.split(":");

            /* It is like off by one bit. Last splitted has size 1,
               which we want to avoid
            */
            if(splitted.size()>1) {
                votersList.append(splitted.at(0) + ":" + splitted.at(1));
            }
        }while(!votersLine.isNull());
    }

    userCombo = new QComboBox();
    userCombo->addItem("Choose Name");
    userCombo->addItems(votersList);
    layout->addWidget(userCombo);

    comboSize = list.size();

    comboBoxes = new QList<QComboBox *>();

    for(int i=0; i < comboSize; i++) {
        QComboBox *comboBox = new QComboBox();
        comboBox->addItem("Priority " + QString::number(i+1));
        comboBox->setObjectName("comboBox"+QString::number(i));
        comboBox->addItems(list);
        //layout->addWidget(comboBox);
        comboBoxes->append(comboBox);
    }

    for(int i=0; i<comboBoxes->size(); i++) {
        layout->addWidget(comboBoxes->at(i));
    }

    ui->scrollArea->setLayout(layout);
}

QList<QString> VoteDialog::getVote()
{
    /* Lets get values from each combobox */
    QList<QString> list;
    list.append(userCombo->currentText());

    for(int i=0; i< comboBoxes->size(); i++) {
        QComboBox *comboBox = comboBoxes->at(i);
        QString currentText = comboBox->currentText();
        list.append(currentText);
    }

    return list;
}

VoteDialog::~VoteDialog()
{
    delete ui;
}
