#ifndef VOTEDIALOG_H
#define VOTEDIALOG_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QComboBox>

namespace Ui {
    class VoteDialog;
}

class VoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoteDialog(QWidget *parent = 0);
    QList<QString> getVote();
    ~VoteDialog();

private:
    Ui::VoteDialog *ui;
    QComboBox *userCombo;
    QList<QComboBox *> *comboBoxes;
    int comboSize;
};

#endif // VOTEDIALOG_H
