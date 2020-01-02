#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <QFile>
#include<QJsonObject>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
//const QString fileName = "../ATetris/json/settings.json";
const QString fileName = "./json/settings.json";
class SettingsManager
{
private:
      QMap<QString,int> keyMappings;
public:

    QJsonObject settings;
    SettingsManager();
    void readSettingFile();
    void initKeyMapping();
    int getBindingKey(const QString &op);
    QMap<QString,int>& getKeyMappings(){
        return this->keyMappings;
    }
    int getKey(QString s){
        return keyMappings[s];
    }
    void saveSettings();
};

#endif // SETTINGSMANAGER_H
