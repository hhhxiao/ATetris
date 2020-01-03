#ifndef KEYPRESSMANAGER_H
#define KEYPRESSMANAGER_H

#include <QKeyEvent>
#include <QTimer>
#include <QWidget>
#include "settingsmanager.h"

//这里的按键检测代码能简化

class StartWindow;
enum ArrEventType{MOVE_LEFT,MOVE_RIGHT};
class KeyPressManager: public QObject
{
    Q_OBJECT
private:
    StartWindow *window;
    int das = 100;
    int arr = 20;
    int dropArr = 100;
    int dropDas = 20;



    int hardDrop = Qt::Key_Space;
    int moveRight = Qt::Key_Right;
    int moveLeft = Qt::Key_Left;
    int drop = Qt::Key_Down;
    int leftRotate = Qt::Key_Z;
    int rightRotate = Qt::Key_X;
    int pauseDropTimer = Qt::Key_P;
    int hold = Qt::Key_Shift;

    ArrEventType eventType = MOVE_LEFT;
   QTimer *dasTimer,*arrTimer;
   QTimer *softDropDas,*softDropArr;
public:
    void setWindow(StartWindow *window);
    KeyPressManager(StartWindow *window);
    KeyPressManager();
    void keyPressHandler(QKeyEvent *ev);
    void keyReleaseHanler(QKeyEvent *ev);
    void initSetting(SettingsManager *manager);

public slots:
    void arrEvent();
    void startArrTimer();
    void softDropArrEvent();
    void startSoftDropArrTimer();

};

#endif // KEYPRESSMANAGER_H
