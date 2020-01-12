#include "./windows/mainwindow.h"

#include <QApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QtDebug>
#include <QKeySequence>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QScreen>
#include <QRect>
#include <QLibrary>
#include "./widget/gamewidget.h"
#include <QTextCodec>
#include <QFontDatabase>
#include <QObject>



//https://www.bbsmax.com/A/6pdDEAYkzw/





void applicationInit(){
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    C::SCREEN_HEIGHT = screenGeometry.height();
    C::SCREEN_WIDTH = screenGeometry.width();
    C::WIDTH = C::SCREEN_HEIGHT / 30;
    qDebug()<<screenGeometry.height()<<"   "<<screenGeometry.width();
}


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

//class TestClass: public QObject
//{
//private:
//    QTimer *timer;
//    CCBot *bot;
//    GameMap *map;
//    SeqBase *seq;
//};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"Hello world";

    MainWindow w;
    applicationInit();
    w.show();
    return a.exec();
}
