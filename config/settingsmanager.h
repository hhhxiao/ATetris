#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <QFile>
#include<QJsonObject>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include "../tetromino/tetro.h"
const QString fileName = "../ATetris/json/settings.json";
//const QString fileName = "./json/settings.json";
class SettingsManager
{
private:
    //  QMap<QString,int> keyMappings;
      QJsonObject settings;
public:

    SettingsManager();
    void readSettingFile();
    void initKeyMapping();
    void saveSettings(QMap<QString,int>&);
    void loadSettings();
    //    int getBindingKey(const QString &op);

};

#endif // SETTINGSMANAGER_H
