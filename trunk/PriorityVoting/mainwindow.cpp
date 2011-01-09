#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "voterdialog.h"
#include "catagorydialog.h"
#include "votedialog.h"
#include "priorityfile.h"
#include "priorityconsole.h"
#include "priorityfind.h"
#include "priorityutil.h"
#include "votingsettingsdialog.h"
#include <QTextStream>
#include <QFile>
#include "vote.h"
#include "votingsettings.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/* Manage voters. These are individual people who vote */
void MainWindow::OnVoterClicked()
{
    // Let's show the VoterDialog
    VoterDialog *dialog = new VoterDialog();
    QString data;

    if(dialog->exec() == QDialog::Accepted) {       
        data = dialog->getVoters();

        QStringList list = data.split("\n");
        QTextStream out(stdout);
        QStringList formattedList;

        for(int i=0; i<list.size(); i++) {
            /* Let's make it blank proof. Might not be best solution but works for our purpose */
            QString item = list.at(i);
            item = item.simplified();

            // Use only one : on multiple times Ok clicked
            QRegExp reg("^\\d+:(\\?*)");
            item.replace(reg, reg.cap(1));


            if(item!="") {
                // We got a non-blank name of voter. Let's save the voter with an id
                // We will use duplicate name, because two persons can have same name
                // Our differentiator thus will be the id of the Voter.               
                formattedList.append(item);
            }
        }

        // We have formatted data in formattedList let's save it to a file
        // Later we may choose to use XML or database. Now let's save it in a text file
        // Before saving let's reformat our list to include voter's id and :

        QList<QString> formattedVotersList;

        for(int i = 0; i < formattedList.size(); i++) {
            QString format = QString::number(i + 1) + ":"; /* Let's make id start from 1 */
            format += formattedList.at(i);

            formattedVotersList.append(format);
        }

        if(PriorityFile::writeToFile(formattedVotersList, "voters.txt")) {
            statusBar()->showMessage("Voters Saved");
        } else {
            statusBar()->showMessage("Voters Save Failed");
        }
    }
}

/* Manage Catagory/Candidate of voting. People vote to get catagory or be one candidate */
void MainWindow::OnCatagoryClicked()
{
    CatagoryDialog *dialog = new CatagoryDialog();
    QString data;
    if(dialog->exec()==QDialog::Accepted) {
        data = dialog->getCatagories();
        QStringList list = data.split("\n");
        QStringList formattedList;

        for(int i=0; i<list.size(); i++) {
            /* Let's make it blank proof. Might not be best solution but works for our purpose */
            QString item = list.at(i);
            item = item.simplified();

            // Use only one : on multiple times Ok clicked
            QRegExp reg("^\\d+:(\\?*)");
            item.replace(reg, reg.cap(1));


            if(item!="") {
                // We got a non-blank name of catagory. Let's save the catagory with priority
                formattedList.append(item);
            }
        }

        QList<QString> formattedCatagoriesList;

        for(int i = 0; i < formattedList.size(); i++) {
            QString format = QString::number(i+1) + ":"; /* Lets make id start from 1 */
            format += formattedList.at(i);

            formattedCatagoriesList.append(format);
        }

        if(PriorityFile::writeToFile(formattedCatagoriesList, "catagories.txt")) {
            statusBar()->showMessage("Catagories Saved");
        } else {
            statusBar()->showMessage("Catagories Save Failed");
        }

    }
}

/* Inidividual voting on the voting window activated by this */
void MainWindow::OnVoteClicked()
{
    /* This code sucks for now. I'll see later */

    VoteDialog *dialog = new VoteDialog();
    if(dialog->exec()==QDialog::Accepted) {

        /* Lets leave out error checking for now and assume user is good and chooses
           three different priorities and unique name */
        /* We will save all priorities, corresponding name when saved */

        QList<QString> votes = dialog->getVote();

        // PriorityConsole::print(votes);

        int votesSize = votes.size();
        QString formattedVote;
        QString fileName = "votes.txt";

        /* Format of votes.txt */
        // Voter, Voting, priority1:Candidate, priority2:Candidate
        // E.g 5, 1, 1:3, 2:1, 3:2

        for(int i=1; i<votesSize; i++) {
            QString sCandidateName = votes.at(i);
            Candidate candiate = PriorityFind::findCandidate(sCandidateName);
            formattedVote.append(i+":"+candiate.getId());

            //vote->addCandidatePriority(candidate, i);
        }

        if(PriorityFile::appendToFile(formattedVote, fileName)) {
            /* Lets show message for 5 seconds only.
               We don't want to distract other voters
            */
            statusBar()->showMessage("Vote saved", 5000);
        } else {
            statusBar()->showMessage("Vote save failed", 5000);
        }
    }
}

/* After voting, result is calculated and shown to the tblVotingResult */
void MainWindow::OnResultClicked()
{

    QTextStream out(stdout);
    out << "Result Clicked";

    QMap<int, QString> *results = new QMap<int, QString>();
    results = &PriorityUtil::calculateResult();

    /* See candidateLimit set vot** from PriorityUtil and then call that object */

    QStandardItemModel *model = new QStandardItemModel;
    model->setHorizontalHeaderLabels(QStringList() << "Voter" << "Catagory");

    QMapIterator<int, QString> i(*results);

    //PriorityConsole::print(QString::number(results->size()));

    while (i.hasNext()) {
        i.next();
        int voterId = i.key();
        Voter voter = PriorityFind::findVoter(voterId);

        QString candidateIdPriority = i.value();
        QList<QString>candidatePriorities = candidateIdPriority.split(",");
        QString scandidateId = candidatePriorities.at(0);
        QString spriority = candidatePriorities.at(1);
        int candidateId = scandidateId.toInt();
        Candidate candidate = PriorityFind::findCandidate(candidateId);


        QList<QStandardItem*> items;
        QString voterName = voter.getName();
        QString candidateName = candidate.getName();

        items.append(new QStandardItem(voterName));
        items.append(new QStandardItem(QString::number(candidate.getId()) + ":"
                                       + candidateName+" at priority "+spriority));

        model->appendRow(items);
     }

    ui->tblVotingResult->setModel(model);
}

/* We may want to save current voting result for further voting on same issue */
void MainWindow::OnSaveResultClicked()
{
    QTextStream out(stdout);
    out << "Result Save Clicked";
}

void MainWindow::OnClearVotesClicked()
{    
    if(PriorityFile::clearFile("votes.txt")) {
        statusBar()->showMessage("Votes Cleared");
    } else {
        statusBar()->showMessage("Votes Cleared Failed");
    }
}

void MainWindow::OnVotingSettingsClicked()
{
    VotingSettingsDialog *dialog = new VotingSettingsDialog();
    QString data;

    if(dialog->exec()==QDialog::Accepted) {
        data = dialog->getVotingSettings();
        QStringList list = data.split("\n");

        /* Let's save different settings on related files */
        /* Here we save system(f, i), active, reference
           e.g f, 2, 1
           i.e We use f(favorable), i(infavorable), active(current active vote), reference(old)
         */

        PriorityFile::writeToFile(list.at(0), "settings.txt");

        /* Let's recreate votting list. We want to avoid blank lines at last */

        QList<QString> votingList;

        /* We start from second index */
        for(int i=1; i<list.size(); i++) {
            QString line = list.at(i);
            line = line.simplified();
            if(line!="")
                votingList.append(line);
        }

        PriorityFile::writeToFile(votingList, "votings.txt");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
