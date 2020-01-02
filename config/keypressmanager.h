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
    StartWindow *widow;
    int hardDrop = Qt::Key_Space;
    int moveRight = Qt::Key_Right;
    int moveLeft = Qt::Key_Left;
    int drop = Qt::Key_Down;
    int leftRotate = Qt::Key_Z;
    int rightRotate = Qt::Key_X;
    int pauseDropTimer = Qt::Key_P;

    ArrEventType eventType = MOVE_LEFT;
   QTimer *dasTimer,*arrTimer;
   QTimer *softDropDas,*softDropArr;
public:
    static const int DAS;
    static const int ARR;
    void setWindow(StartWindow *window);
    KeyPressManager(StartWindow *window);
    KeyPressManager();
    void keyPressHandler(QKeyEvent *ev);
    void keyReleaseHanler(QKeyEvent *ev);
    void setKeyBinding(SettingsManager *manager);

public slots:
    void arrEvent();
    void startArrTimer();
    void softDropArrEvent();
    void startSoftDropArrTimer();

};

#endif // KEYPRESSMANAGER_H
