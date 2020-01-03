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
    QJsonObject keys = manager->getkeyBinding();
    ui->leftMoveCb->setCurrentText(keys.value("moveLeft").toString());
    ui->rightMoveCb->setCurrentText(keys.value("moveRight").toString());
    ui->hardDropCb->setCurrentText(keys.value("hardDrop").toString());
    ui->softDropCb->setCurrentText(keys.value("softDrop").toString());
    ui->holdCb->setCurrentText(keys.value("hold").toString());
    ui->GravityCb->setCurrentText(keys.value("pause").toString());
    ui->leftRotateCb->setCurrentText(keys.value("leftRotate").toString());
    ui->rightRotateCb->setCurrentText(keys.value("rightRotate").toString());


    ui->dasVal->setNum(manager->getDas());
    ui->arrVal->setNum(manager->getArr());
    ui->DropArrVal->setNum(manager->getDropArr());
    ui->dropDasVal->setNum(manager->getDropDas());
    ui->lockTimeVal->setNum(manager->getLockTime());

    ui->dasHs->setMaximum(200);
    ui->ArrHs->setMaximum(99);
    ui->dropArrHs->setMaximum(99);
    ui->dropDasHs->setMaximum(200);
    ui->LockTimeHs->setMaximum(999);

    ui->dasHs->setMinimum(1);
    ui->ArrHs->setMinimum(1);
    ui->dropArrHs->setMinimum(1);
    ui->dropDasHs->setMinimum(1);
    ui->LockTimeHs->setMinimum(1);

    ui->dasHs->setValue(manager->getDas());
    ui->ArrHs->setValue(manager->getArr());
    ui->dropArrHs->setValue(manager->getDropArr());
    ui->dropDasHs->setValue(manager->getDropDas());
    ui->LockTimeHs->setValue(manager->getLockTime());


    connect(ui->dasHs, SIGNAL(valueChanged(int)), ui->dasVal, SLOT(setNum(int)));
    connect(ui->ArrHs, SIGNAL(valueChanged(int)), ui->arrVal, SLOT(setNum(int)));
    connect(ui->dropArrHs, SIGNAL(valueChanged(int)), ui->DropArrVal, SLOT(setNum(int)));
    connect(ui->dropDasHs, SIGNAL(valueChanged(int)), ui->dropDasVal, SLOT(setNum(int)));
     connect(ui->LockTimeHs, SIGNAL(valueChanged(int)), ui->lockTimeVal, SLOT(setNum(int)));
}

SettingsWidnow::~SettingsWidnow()
{
    delete ui;
}

void SettingsWidnow::on_save_clicked()
{
    QJsonObject &keys = manager->getkeyBinding();
    keys["moveLeft"] = ui->leftMoveCb->currentText();
    keys["moveRight"] = ui->rightMoveCb->currentText();
    keys["hardDrop"] = ui->hardDropCb->currentText();
    keys["softDrop"] = ui->softDropCb->currentText();
    keys["hold"] = ui->holdCb->currentText();
    keys["rightRotate"] = ui->rightRotateCb->currentText();
    keys["pause"] = ui->GravityCb->currentText();
    keys["leftRotate"] = ui->leftRotateCb->currentText();
    QJsonObject &sen = manager->getSensitivity();
    sen["arr"]=ui->ArrHs->value();
    sen["das"]=ui->dasHs->value();
    sen["dropArr"]=ui->dropArrHs->value();
    sen["dropDas"]=ui->dropDasHs->value();
    sen["lockTime"]=ui->LockTimeHs->value();
    manager->saveSettings();
}

void SettingsWidnow::on_exit_clicked()
{
    this->close();
}
