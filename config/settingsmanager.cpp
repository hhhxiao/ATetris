#include "settingsmanager.h"

SettingsManager::SettingsManager()
{
    readSettingFile();
}

void SettingsManager::readSettingFile()
{
    QFile settingFile(fileName);
    if(!settingFile.exists()){
         qDebug() << "file don't exist";
    }
    if(!settingFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "could not read SettingFile";
        return;
    }
    QByteArray mText = settingFile.readAll();
    settingFile.close();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(mText, &json_error));
    this->settings = jsonDoc.object();
    for(auto i = C::KEY_MAP.begin();i!=C::KEY_MAP.end();++i){
        C::KEY_MAP[i.key()] = settings.value(i.key()).toInt();
    }
}

//void SettingsManager::initKeyMapping()
//{
//    for(int keyCode = '0';keyCode<='Z';++keyCode)
//        keyMappings.insert(QString(keyCode),keyCode);
//    keyMappings.insert("Shift",Qt::Key_Shift);
//    keyMappings.insert("Ctrl",Qt::Key_Control);
//    keyMappings.insert("Alt",Qt::Key_Alt);
//    keyMappings.insert("Left",Qt::Key_Left);
//    keyMappings.insert("Right",Qt::Key_Right);
//    keyMappings.insert("Up",Qt::Key_Up);
//    keyMappings.insert("Down",Qt::Key_Down);
//    keyMappings.insert("Space",Qt::Key_Space);
//}

//int SettingsManager::getBindingKey(const QString &op)
//{
//    QString keyStr =  keyBinding.value(op).toString();
//    qDebug()<<op<<"   key is"<<keyStr<<"keyCode is  "<<getKey(keyStr);
//    return this->getKey(keyStr);

//}

void SettingsManager::saveSettings(QMap<QString,int>& changed)
{
    QFile settingFile(fileName);
    if(!settingFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "could not read SettingFile";
        return;
    }

    QJsonDocument jsonDoc;
    for(auto i = changed.begin();i!=changed.end();++i){
        qDebug()<<"key "<<i.key()<<"  value  "<<i.value();
        settings[i.key()] = i.value();
        C::KEY_MAP[i.key()] = i.value();
    }

    jsonDoc.setObject(settings);
    settingFile.write(jsonDoc.toJson());
    settingFile.flush();
    settingFile.close();
}

