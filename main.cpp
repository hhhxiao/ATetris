#include "./windows/mainwindow.h"

#include <QApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QtDebug>
#include <QKeySequence>
#include <QKeyEvent>
//https://www.bbsmax.com/A/6pdDEAYkzw/
QString readQss(const QString fileName){
    QFile qss(fileName);

    if( qss.open(QFile::ReadOnly)) {
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        qss.close();
        return style;
    }
    else
    {  qDebug("Open failed");
    }
    return "";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<a.applicationDirPath();
    MainWindow w;
    QString styleSheet = readQss(":/style/style/gray.css");
    a.setStyleSheet(styleSheet);
    w.show();
    return a.exec();
}
