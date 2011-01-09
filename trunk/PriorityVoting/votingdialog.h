#ifndef VOTINGDIALOG_H
#define VOTINGDIALOG_H

#include <QDialog>

namespace Ui {
    class VotingDialog;
}

class VotingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VotingDialog(QWidget *parent = 0);
    ~VotingDialog();

private:
    Ui::VotingDialog *ui;
};

#endif // VOTINGDIALOG_H
