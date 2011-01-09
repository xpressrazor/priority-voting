#ifndef VOTERDIALOG_H
#define VOTERDIALOG_H

#include <QDialog>

namespace Ui {
    class VoterDialog;
}

class VoterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoterDialog(QWidget *parent = 0);
    ~VoterDialog();
    QString getVoters();

private:
    Ui::VoterDialog *ui;
};

#endif // VOTERDIALOG_H
