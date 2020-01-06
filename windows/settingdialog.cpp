#include "settingdialog.h"
#include "ui_settingdialog.h"

void SettingDialog::initKeyMapping()
{
    for(int keyCode = '0';keyCode<='Z';++keyCode)
        keyMapTable.insert(keyCode,QString(keyCode));
    keyMapTable.insert(Qt::Key_Shift,"Shift");
    keyMapTable.insert(Qt::Key_Shift,"Shift");
    keyMapTable.insert(Qt::Key_Control,"Ctrl");
    keyMapTable.insert(Qt::Key_Alt,"Alt");
    keyMapTable.insert(Qt::Key_Left,"Left");
    keyMapTable.insert(Qt::Key_Right,"Right");
    keyMapTable.insert(Qt::Key_Up,"Up");
    keyMapTable.insert(Qt::Key_Down,"Down");
    keyMapTable.insert(Qt::Key_Space,"Space");

}

SettingDialog::SettingDialog(SettingsManager*settingManager,QWidget *parent) :

    QDialog(parent),
    ui(new Ui::SettingDialog), manager(settingManager)
{
    chosen = nullptr;
    ui->setupUi(this);
    initKeyMapping();
    btn_table = {
        {"moveLeft",ui->moveLeftBtn},
        {"moveRight",ui->moveRightBtn},
        {"leftRotate",ui->leftRotateBtn},
        {"rightRotate",ui->rightRotateBtn},
        {"hardDrop",ui->hardDropBtn},
        {"softDrop",ui->softDropBtn},
        {"hold",ui->holdBtn}
    };
    for(auto i = btn_table.begin();i!=btn_table.end();++i){
        int keyCode = C::KEY_MAP[i.key()];
        QString keyValue = keyMapTable[keyCode];
        if(keyValue == "")
            keyValue = "unknown";
        i.value()->setText(keyValue);
    }

    ui->arr->setRange(0,40);
    ui->das->setRange(0,200);
    ui->softSpeed->setRange(0,100);
    ui->lockDelay->setRange(0,1000);
    ui->arr->setValue(C::KEY_MAP["arr"]);
    ui->das->setValue(C::KEY_MAP["das"]);
    ui->softSpeed->setValue(C::KEY_MAP["dropArr"]);
    ui->lockDelay->setValue(C::KEY_MAP["lockTime"]);
}
SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::keyPressEvent(QKeyEvent *ev)
{
    if(chosen){
        for(auto i = btn_table.begin();i!=btn_table.end();i++){
            if(i.value() == chosen){
                tempTable[i.key()] = ev->key();
                break;
            }

        }
        QString keyValue = keyMapTable[ev->key()];
        if(keyValue == "")
            keyValue = "unknown";
        chosen->setText(keyValue);
    }
}

void SettingDialog::on_moveRightBtn_clicked(){
    chosen =ui->moveRightBtn;
    this->setFocus();
}

void SettingDialog::on_moveLeftBtn_clicked()
{
    chosen = ui->moveLeftBtn;
    this->setFocus();

}

void SettingDialog::on_leftRotateBtn_clicked()
{
    chosen = ui->leftRotateBtn;
    this->setFocus();
}

void SettingDialog::on_rightRotateBtn_clicked()
{
    chosen = ui->rightRotateBtn;
    this->setFocus();
}

void SettingDialog::on_hardDropBtn_clicked()
{
    chosen = ui->hardDropBtn;
    this->setFocus();
}

void SettingDialog::on_softDropBtn_clicked()
{
    chosen = ui->softDropBtn;
    this->setFocus();
}

void SettingDialog::on_holdBtn_clicked()
{
    chosen = ui->holdBtn;
    this->setFocus();
}

void SettingDialog::on_buttonBox_accepted()
{
    //这里把设置写到内存和本地
    tempTable.insert("das",ui->das->value());
    tempTable.insert("arr",ui->arr->value());
    tempTable.insert("dropArr",ui->softSpeed->value());
    tempTable.insert("lockTime",ui->lockDelay->value());
    manager->saveSettings(tempTable);
    this->accept();
}
