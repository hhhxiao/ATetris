#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->settingManager = new SettingsManager();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete modeWindow;
    delete ui;
}


void MainWindow::on_settingButton_clicked()
{
    this->settingDialog = new SettingDialog(this->settingManager);
    settingDialog->show();

}

void MainWindow::on_modeCreatorButton_clicked()
{
    this->modeWindow = new ModeWindow();
    modeWindow->show();
}

void MainWindow::on_maraBtn_clicked()
{

}

void MainWindow::on_c4wBtn_clicked()
{

         ModeBase *base =  new C4wMode();
         SingleGameWindow *game = new SingleGameWindow(base);
          game->show();
}

void MainWindow::on_FortyBtn_clicked()
{
        ModeBase *base =  new FortyMode();
       SingleGameWindow *game = new SingleGameWindow(base);
        game->show();
}

bool MainWindow::checkWindowOpen()
{
        QMessageBox *msgBox;
        msgBox = new QMessageBox("通知",
            "已经有一个窗口在运行",
            QMessageBox::Critical,
            QMessageBox::Ok | QMessageBox::Default,
            QMessageBox::Cancel | QMessageBox::Escape,
            0);
        msgBox->show();
        return true;
}
