#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "startwindow.h"
#include "settingsWindow.h"
#include "modewindow.h"
#include "./config/settingsmanager.h"
#include "./config/keypressmanager.h"
#include <QLineEdit>
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
    void on_beginGame_clicked();
    void on_test_clicked();
    void on_settingButton_clicked();
    void on_modeCreatorButton_clicked();

private:
    KeyPressManager *keyManager;
    SettingsManager *settingManager;
    Ui::MainWindow *ui;
    StartWindow *startWindow;
    SettingsWidnow *settingWindow;
    ModeWindow *modeWindow;

};

#endif // MAINWINDOW_H
