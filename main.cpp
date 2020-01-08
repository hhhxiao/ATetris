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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"Hello world";

//    CCOptions options;
//       CCWeights weights;
//       CCAsyncBot *bot;
//       CCMove move;
//       bool field[400];
//       cc_default_options(&options);
//       cc_default_weights(&weights);
//       bot=cc_launch_async(&options,&weights);
//       int i;
//       for(i=0;i<400;i++){
//           field[i]=0;
//       }
//       cc_reset_async(bot,field,false,0);
//       cc_add_next_piece_async(bot,CC_I);
//       cc_add_next_piece_async(bot,CC_J);
//       cc_add_next_piece_async(bot,CC_T);
//       cc_add_next_piece_async(bot,CC_L);
//       cc_add_next_piece_async(bot,CC_O);
//       cc_add_next_piece_async(bot,CC_S);
//       cc_request_next_move(bot);
//       for(int i = 0;i<4;i++){
//           if(!cc_poll_next_move(bot,&move))
//            qDebug()<<move.movement_count;
//           cc_request_next_move(bot);
//       }
    //设置字体
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    int index = QFontDatabase::addApplicationFont(":/style/style/simhei.ttf");
//    if(index != -1)
//    {
//        QStringList fontList(QFontDatabase::applicationFontFamilies(index)); /* font -- LiHei Pro */
//        if(fontList.count() > 0)
//        {
//            QFont font_zh(fontList.at(0));
//            font_zh.setBold(false);
//            a.setFont(font_zh);
//        }
//    }
//    qDebug()<<a.applicationDirPath();
    MainWindow w;
    applicationInit();
    QString styleSheet = readQss(":/style/style/gray.css");
    a.setStyleSheet(styleSheet);
    w.show();
    return a.exec();
}
