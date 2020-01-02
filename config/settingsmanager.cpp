#include "settingsmanager.h"

SettingsManager::SettingsManager()
{
    readSettingFile();
    initKeyMapping();
}

void SettingsManager::readSettingFile()
{
    QFile settingFile(":/config/json/settings.json");
    if(!settingFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "could not read SettingFile";
        return;
    }
    QByteArray mText = settingFile.readAll();
    settingFile.close();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(mText, &json_error));
    this->settings = jsonDoc.object();
}

void SettingsManager::initKeyMapping()
{
    for(int keyCode = '0';keyCode<='Z';++keyCode)
        keyMappings.insert(QString(keyCode),keyCode);
    keyMappings.insert("Shift",Qt::Key_Shift);
    keyMappings.insert("Ctrl",Qt::Key_Control);
    keyMappings.insert("Alt",Qt::Key_Alt);
    keyMappings.insert("Left",Qt::Key_Left);
    keyMappings.insert("Right",Qt::Key_Right);
    keyMappings.insert("Up",Qt::Key_Up);
    keyMappings.insert("Down",Qt::Key_Down);
    keyMappings.insert("Space",Qt::Key_Space);
}

int SettingsManager::getBindingKey(const QString &op)
{
    auto keyBinding =   settings.value("keyBinding").toObject();
    QString keyStr =  keyBinding.value(op).toString();
    qDebug()<<op<<"   key is"<<keyStr<<"keyCode is  "<<getKey(keyStr);
    return this->getKey(keyStr);

}
