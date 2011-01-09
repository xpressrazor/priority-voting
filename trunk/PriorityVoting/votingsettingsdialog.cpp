#include "votingsettingsdialog.h"
#include "ui_votingsettingsdialog.h"
#include "priorityfile.h"
#include "priorityfind.h"
#include "priorityconsole.h"
#include "votingdialog.h"
#include "candidate.h"

VotingSettingsDialog::VotingSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VotingSettingsDialog)
{
    // Let's show previous settings from settings.txt if there were some
    ui->setupUi(this);

    /* Get list from vottings.txt, settings.txt and add to the comboboxes */
    QList<QString> settingsList = PriorityFile::readFile("settings.txt");    
    ui->textVotings->append(settingsList.at(0));    
    /* Let's find active and reference */

    QList<QString> votingsList = PriorityFile::readFile("votings.txt");
    QStringList votingNamesId;
    /* At least let's use curly braces for for loop */
    for(int i=0; i<votingsList.size(); i++) {
        ui->textVotings->append(votingsList.at(i));

        QStringList tempVotingNamesId = votingsList.at(i).split(",");
        votingNamesId.append(tempVotingNamesId.at(0) + ":" + tempVotingNamesId.at(1));
    }

    //QList<QString>candidatesList = PriorityFile::readFile("catagories.txt");


    /* Let's fill our comboboxes with votingsList */
    ui->cmbActive->addItem("Set Active");
    ui->cmbReference->addItem("Set Reference");
    ui->cmbActive->addItems(votingNamesId);
    ui->cmbReference->addItems(votingNamesId);

     QStringList tempSettingsOldNewList = settingsList.at(0).split(",");
     QString sactive = tempSettingsOldNewList.at(1);
     QString sreference;
     if(tempSettingsOldNewList.size()>2)
         sreference = tempSettingsOldNewList.at(2);

     //PriorityConsole::print(sactive);
     //PriorityConsole::print(sreference);

     sactive = sactive.simplified();
     sreference = sreference.simplified();

     /*
     int active = sactive.toInt();
     int referecene = sreference.toInt();
     */
     if(!sactive.isEmpty()) {
         ui->cmbActive->setCurrentIndex(sactive.toInt());
     }

     if(!sreference.isEmpty()) {
         ui->cmbReference->setCurrentIndex(sreference.toInt());
     }
}

QString VotingSettingsDialog::getVotingSettings()
{
    return ui->textVotings->toPlainText();
}

void VotingSettingsDialog::OnAddVoting()
{
    QTextStream out(stdout);
    out << "On Add Voting clicked";
}

VotingSettingsDialog::~VotingSettingsDialog()
{
    delete ui;
}
