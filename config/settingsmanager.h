#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <QFile>
#include<QJsonObject>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
class SettingsManager
{
public:
    QMap<QString,int> keyMappings;
    QJsonObject settings;
    SettingsManager();
    void readSettingFile();
    void initKeyMapping();
    int getBindingKey(const QString &op);
    const QMap<QString,int>& getKeyMappings()const{
        return this->keyMappings;
    }
    int getKey(QString s){
        return keyMappings[s];
    }
};

#endif // SETTINGSMANAGER_H
