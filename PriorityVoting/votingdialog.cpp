#include "votingdialog.h"
#include "ui_votingdialog.h"

VotingDialog::VotingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VotingDialog)
{
    ui->setupUi(this);
}

VotingDialog::~VotingDialog()
{
    delete ui;
}
