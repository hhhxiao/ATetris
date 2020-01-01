#ifndef KEYPRESSMANAGER_H
#define KEYPRESSMANAGER_H

#include <QKeyEvent>

class StartWindow;
class KeyPressManager
{
private:
    StartWindow *widow;
    int hardDrop = Qt::Key_Space;
    int moveRight = Qt::Key_Right;
    int moveLeft = Qt::Key_Left;
    int drop = Qt::Key_Down;
    int leftRotate = Qt::Key_Z;
    int rightRotate = Qt::Key_X;
public:

    void setWindow(StartWindow *window);
    KeyPressManager(StartWindow *window);
    KeyPressManager();
    void keyPressHandler(QKeyEvent *ev);
    void keyReleaseHanler(QKeyEvent *ev);
};

#endif // KEYPRESSMANAGER_H
