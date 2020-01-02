#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>

namespace Ui {
class Settings;
}

class SettingsWidnow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsWidnow(QWidget *parent = nullptr);
    ~SettingsWidnow();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
