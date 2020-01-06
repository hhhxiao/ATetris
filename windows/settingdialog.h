#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QMap>
#include "../tetromino/c.h"
#include <QKeyEvent>
#include <QtDebug>
#include "../config/settingsmanager.h"
namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT
private:
    void initKeyMapping();
public:
    explicit SettingDialog(SettingsManager*settingManager, QWidget *parent = nullptr);
    ~SettingDialog();

private:
    void keyPressEvent(QKeyEvent *) override;
    Ui::SettingDialog *ui;
    QMap<int,QString> keyMapTable;
    QMap<QString,QPushButton*> btn_table;
    QMap<QString,int> tempTable;
    SettingsManager *manager;
    QPushButton *chosen;
private slots:
    void chooseBtn(QPushButton *b){this->chosen = b;}
    void on_moveRightBtn_clicked();
    void on_moveLeftBtn_clicked();
    void on_leftRotateBtn_clicked();
    void on_rightRotateBtn_clicked();
    void on_hardDropBtn_clicked();
    void on_softDropBtn_clicked();
    void on_holdBtn_clicked();
    void on_buttonBox_accepted();
};

#endif // SETTINGDIALOG_H
