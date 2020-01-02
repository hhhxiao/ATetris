#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_beginGame_clicked()
{
    this->startWindow = new StartWindow();
    startWindow->show();
    this->close();
}


void MainWindow::on_test_clicked()
{


}
