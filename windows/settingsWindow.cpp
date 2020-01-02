#include "settingsWindow.h"
#include "ui_settingsWindow.h"
#include <QMap>
#include <QObject>
SettingsWidnow::SettingsWidnow(SettingsManager *manager,QWidget *parent):
    QMainWindow(parent),
  ui(new Ui::Settings),manager(manager)
{
    ui->setupUi(this);
    QMap<QString,int> map = manager->getKeyMappings();
    for(auto iter = map.begin();iter!=map.end();++iter){
        ui->leftMoveCb->addItem(iter.key());
        ui->rightMoveCb->addItem(iter.key());
        ui->hardDropCb->addItem(iter.key());
        ui->softDropCb->addItem(iter.key());
        ui->holdCb->addItem(iter.key());
        ui->GravityCb->addItem(iter.key());
        ui->leftRotateCb->addItem(iter.key());
        ui->rightRotateCb->addItem(iter.key());
    }
    QJsonObject keys = manager->settings.value("keyBinding").toObject();
    ui->leftMoveCb->setCurrentText(keys.value("moveLeft").toString());
    ui->rightMoveCb->setCurrentText(keys.value("moveRight").toString());
    ui->hardDropCb->setCurrentText(keys.value("hardDrop").toString());
    ui->softDropCb->setCurrentText(keys.value("softDrop").toString());
    ui->holdCb->setCurrentText(keys.value("hold").toString());
    ui->GravityCb->setCurrentText(keys.value("pause").toString());
    ui->leftRotateCb->setCurrentText(keys.value("leftRotate").toString());
    ui->rightRotateCb->setCurrentText(keys.value("rightRotate").toString());
}

SettingsWidnow::~SettingsWidnow()
{
    delete ui;
}

void SettingsWidnow::on_save_clicked()
{
    QJsonObject keys = manager->settings.value("keyBinding").toObject();
    keys["moveLeft"] = ui->leftMoveCb->currentText();
    keys["moveRight"] = ui->rightMoveCb->currentText();
    keys["hardDrop"] = ui->hardDropCb->currentText();
    keys["softDrop"] = ui->softDropCb->currentText();
    keys["hold"] = ui->holdCb->currentText();
    keys["rightRotate"] = ui->rightMoveCb->currentText();
    keys["pause"] = ui->GravityCb->currentText();
    keys["leftRotate"] = ui->leftRotateCb->currentText();
    this->manager->settings["keyBinding"] = keys;
    manager->saveSettings();
}

void SettingsWidnow::on_exit_clicked()
{
    this->close();
}
