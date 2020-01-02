#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->keyManager = new KeyPressManager();
    this->settingManager = new SettingsManager();
    this->keyManager->setKeyBinding(settingManager);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete modeWindow;
    delete startWindow;
    delete settingWindow;
    delete ui;
}

void MainWindow::on_beginGame_clicked()
{
    this->startWindow = new StartWindow(this->keyManager);
    startWindow->show();
   // this->close();
}
void MainWindow::on_test_clicked()
{


}

void MainWindow::on_settingButton_clicked()
{
    this->settingWindow = new SettingsWidnow();
    settingWindow->show();
}

void MainWindow::on_modeCreatorButton_clicked()
{
    this->modeWindow = new ModeWindow();
    modeWindow->show();
}
