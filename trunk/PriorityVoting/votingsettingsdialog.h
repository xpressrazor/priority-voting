#ifndef VOTINGSETTINGSDIALOG_H
#define VOTINGSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class VotingSettingsDialog;
}

class VotingSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VotingSettingsDialog(QWidget *parent = 0);
    QString getVotingSettings();
    ~VotingSettingsDialog();

private slots:
    void OnAddVoting();

private:
    Ui::VotingSettingsDialog *ui;
};

#endif // VOTINGSETTINGSDIALOG_H
