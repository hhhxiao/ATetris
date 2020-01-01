#include "keypressmanager.h"
#include "startwindow.h"
void KeyPressManager::setWindow(StartWindow *window){ this->widow = window;}

KeyPressManager::KeyPressManager(StartWindow *win){
    this->widow = win;
    this->arrTimer = new QTimer(this);
    this->dasTimer = new QTimer(this);
    dasTimer->setSingleShot(true);
    connect(dasTimer,SIGNAL(timeout()),this,SLOT(startArrTimer()));
    connect(arrTimer,SIGNAL(timeout()),this,SLOT(arrEvent()));
}
KeyPressManager::KeyPressManager()=default;
void KeyPressManager::keyPressHandler(QKeyEvent *ev)
{
    if(ev->key() == this->drop){
        widow->geteTetro()->drop();
    }else if(ev->key() == this->moveLeft){
        this->eventType = MOVE_LEFT;
        if(!ev->isAutoRepeat()){
            this->arrEvent();
            dasTimer->start(DAS);
        }
    }else if(ev->key() == this->moveRight){
        this->eventType = MOVE_RIGHT;
        if(!ev->isAutoRepeat()){
            this->arrEvent();
            dasTimer->start(DAS);
        }
    }else if(ev->key() == this->hardDrop){
        if(!ev->isAutoRepeat()){//防止长按一直转
            widow->geteTetro()->hardDrop();
            widow->getMap()->clearLine();
        }
    }else if(ev->key() == this->leftRotate){
        if(!ev->isAutoRepeat())//防止长按一直转
            widow->geteTetro()->leftRotate();
    }else if(ev->key() == this->rightRotate){
        if(!ev->isAutoRepeat())//防止长按一直转
            widow->geteTetro()->rigthRotate();
    }
}

void KeyPressManager::keyReleaseHanler(QKeyEvent *ev)
{
    if(ev->key() == this->moveLeft){
        if(!ev->isAutoRepeat()){
            this->arrTimer->stop();
            if(this->dasTimer->isActive()){
                this->dasTimer->stop();
            }
        }
    }else if(ev->key() == this->moveRight){
        if(!ev->isAutoRepeat()){
            this->arrTimer->stop();
            if(this->dasTimer->isActive()){
                this->dasTimer->stop();
            }
        }
    }
}

void KeyPressManager::arrEvent()
{
    if(this->eventType == MOVE_LEFT){
        widow->geteTetro()->moveLeft();
    }else {
        widow->geteTetro()->movRight();
    }
}

void KeyPressManager::startArrTimer()
{
   // qDebug()<<"in arr timer";
    this->arrEvent();
    this->arrTimer->start(ARR);
}

const int KeyPressManager::DAS = 100;
const int KeyPressManager::ARR = 40;
