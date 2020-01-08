#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "singlegamewindow.h"
#include "settingdialog.h"
#include "modewindow.h"
#include "./config/settingsmanager.h"
#include "./config/keypressmanager.h"
#include  "./mode/c4wmode.h"
#include <QLineEdit>
#include <QMessageBox>
#include"botbattle.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_settingButton_clicked();

    void on_modeCreatorButton_clicked();

    void on_maraBtn_clicked();

    void on_c4wBtn_clicked();

    void on_FortyBtn_clicked();

private:
    bool checkWindowOpen();
    SettingsManager *settingManager;
    Ui::MainWindow *ui;
    SettingDialog *settingDialog;
    ModeWindow *modeWindow;

};

#endif // MAINWINDOW_H
