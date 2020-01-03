#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <QFile>
#include<QJsonObject>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
const QString fileName = "../ATetris/json/settings.json";
//const QString fileName = "./json/settings.json";
class SettingsManager
{
private:
      QMap<QString,int> keyMappings;
      QJsonObject settings;
      QJsonObject keyBinding;
      QJsonObject sensitivity;
public:

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

    QJsonObject& getkeyBinding(){
        return  this->keyBinding;
    }
    QJsonObject& getSensitivity(){
        return this->sensitivity;
    }

    int getArr(){ return  this->sensitivity.value("arr").toInt();  }
    int getDas(){return  this->sensitivity.value("das").toInt();}
    int getDropDas(){return  this->sensitivity.value("dropArr").toInt();}
    int getDropArr(){return  this->sensitivity.value("dropDas").toInt();}
    int getLockTime(){return  this->sensitivity.value("lockTime").toInt();}
};

#endif // SETTINGSMANAGER_H
