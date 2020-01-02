#include "./windows/mainwindow.h"

#include <QApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QtDebug>
#include <QKeySequence>
#include <QKeyEvent>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   MainWindow w;
    w.show();
    return a.exec();
}
