#include "mainwindow.h"

#include <QApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QtDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QJsonObject obj;
//    obj.insert("name","40L");
//    obj.insert("author","xhy");
//    obj.insert("id",12345);
//    obj.insert("playerNum",1);
//    QJsonObject task;
//    task.insert("type","line");
//    task.insert("num",40);
//    obj.insert("task",task);
//    obj.insert("map",QJsonValue::Null);
//    obj.insert("gravity",true);
//    obj.insert("seq","7-bag");

//    QJsonArray filter = {
//       "tst","tsd","tetris"
//    };
//    obj.insert("filter",filter);
//    obj.insert("cheat",false);
//    qDebug()<<obj;
    return a.exec();
}
