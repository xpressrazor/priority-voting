#ifndef CATAGORYDIALOG_H
#define CATAGORYDIALOG_H

#include <QDialog>

namespace Ui {
    class CatagoryDialog;
}

class CatagoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CatagoryDialog(QWidget *parent = 0);
    QString getCatagories();
    ~CatagoryDialog();

private:
    Ui::CatagoryDialog *ui;
};

#endif // CATAGORYDIALOG_H
