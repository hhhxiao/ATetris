#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include "../config/settingsmanager.h"

namespace Ui {
class Settings;
}

class SettingsWidnow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsWidnow(SettingsManager *m,QWidget *parent = nullptr);
    ~SettingsWidnow();
    void setSettingManager(SettingsManager *m){
        this->manager = m;
    }

private slots:
    void on_save_clicked();
    void on_exit_clicked();
private:
    Ui::Settings *ui;
    SettingsManager *manager;
};

#endif // SETTINGS_H
