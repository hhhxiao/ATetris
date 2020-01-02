#include "settingsWindow.h"
#include "ui_settingsWindow.h"

SettingsWidnow::SettingsWidnow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

SettingsWidnow::~SettingsWidnow()
{
    delete ui;
}
