#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void OnVoterClicked();
    void OnCatagoryClicked();
    void OnVoteClicked();
    void OnResultClicked();
    void OnSaveResultClicked();
    void OnClearVotesClicked();
    void OnVotingSettingsClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
