#ifndef KEYPRESSMANAGER_H
#define KEYPRESSMANAGER_H

#include <QKeyEvent>
#include <QTimer>
#include <QWidget>
#include "settingsmanager.h"

//这里的按键检测代码能简化

class SingleGameWindow;
class GameWidget;
class KeyPressManager: public QObject
{
    Q_OBJECT
private:
    GameWidget *gameWidget;
    int das = 100;
    int arr = 20;
    int dropArr = 10;


    QTimer *lDasTimer,*lArrTimer;
    QTimer *rDasTimer,*rArrTimer;
    QTimer *dropTimer;

    int leftMoveKey = Qt::Key_Left;
    int rightMoveKey = Qt::Key_Right;
    int leftRotateKey = Qt::Key_X ;
    int rightRotateKey = Qt::Key_Z;
    int holdKey = Qt::Key_Shift;
    int softDropKey = Qt::Key_Down;
    int hardDropKey = Qt::Key_Space;

public:

    void setGameWidget(GameWidget *widget);
    KeyPressManager(SingleGameWindow *window);
    KeyPressManager();
    void loadSettings();
    void keyPressHandler(QKeyEvent *ev);
    void keyReleaseHanler(QKeyEvent *ev);
    void wheelEventHandler(QWheelEvent *ev);

public slots:
    void startLarr();
    void startRarr();
    void leftEvent();
    void rightEvent();
    void dropEvent();

};

#endif // KEYPRESSMANAGER_H
