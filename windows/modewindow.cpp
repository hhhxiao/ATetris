#include "modewindow.h"
#include "ui_modewindow.h"

ModeWindow::ModeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeWindow)
{
    ui->setupUi(this);
}

ModeWindow::~ModeWindow()
{
    delete ui;
}
