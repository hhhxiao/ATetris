#include "keypressmanager.h"
#include "../windows/startwindow.h"
void KeyPressManager::setWindow(StartWindow *window){
    this->window = window;
}

KeyPressManager::KeyPressManager(StartWindow *win){
    this->window = win;
    this->lArrTimer = new QTimer(this);
    this->lDasTimer = new QTimer(this);
    this->rArrTimer = new QTimer(this);
    this->rDasTimer = new QTimer(this);
    this->dropTimer = new QTimer(this);
    lDasTimer->setSingleShot(true);
    rDasTimer->setSingleShot(true);
    connect(lDasTimer,SIGNAL(timeout()),this,SLOT(startLarr()));
    connect(rDasTimer,SIGNAL(timeout()),this,SLOT(startRarr()));

    connect(lArrTimer,SIGNAL(timeout()),this,SLOT(leftEvent()));
    connect(rArrTimer,SIGNAL(timeout()),this,SLOT(rightEvent()));

    connect(dropTimer,SIGNAL(timeout()),this,SLOT(dropEvent()));

}
KeyPressManager::KeyPressManager():KeyPressManager(nullptr){};
void KeyPressManager::keyPressHandler(QKeyEvent *ev)
{
    if(ev->key() == this->drop){
        if(!ev->isAutoRepeat()){
            this->dropEvent();
            dropTimer->start(dropArr);
        }
    }else if(ev->key() == this->moveLeft){
        if(!ev->isAutoRepeat()){
            this->leftEvent();
            lDasTimer->start(das);
        }
    }else if(ev->key() == this->moveRight){
        if(!ev->isAutoRepeat()){
            this->rightEvent();
            rDasTimer->start(das);
        }
    }else if(ev->key() == this->hardDrop){
        if(!ev->isAutoRepeat()){//防止长按一直转
            window->geteTetro()->hardDrop();
        }
    }else if(ev->key() == this->leftRotate){
        if(!ev->isAutoRepeat())//防止长按一直转
            window->geteTetro()->leftRotate();
    }else if(ev->key() == this->rightRotate){
        if(!ev->isAutoRepeat())//防止长按一直转
            window->geteTetro()->rigthRotate();
    }else if(ev->key() == this->pauseDropTimer) {
        if(!ev->isAutoRepeat()){
        }
    }else if(ev->key() == this->hold){
        if(!ev->isAutoRepeat()){
            window->hold();
        }
    }

}

void KeyPressManager::keyReleaseHanler(QKeyEvent *ev)
{
    if(ev->key() == this->moveLeft){
        if(!ev->isAutoRepeat()){
            this->lArrTimer->stop();
            if(this->lDasTimer->isActive()){
                this->lDasTimer->stop();
            }
        }
    }else if(ev->key() == this->moveRight){
        if(!ev->isAutoRepeat()){
            this->rArrTimer->stop();
            if(this->rDasTimer->isActive()){
                this->rDasTimer->stop();
            }
        }
    }else if(ev->key() == this->drop){
        if(!ev->isAutoRepeat()){
            if(this->dropTimer->isActive())
                dropTimer->stop();
        }
    }

}

void KeyPressManager::initSetting(SettingsManager *manager)
{
    this->hardDrop = manager->getBindingKey("hardDrop");
    this->moveLeft = manager->getBindingKey("moveLeft");
    this->moveRight = manager->getBindingKey("moveRight");
    this->drop = manager->getBindingKey("softDrop");
    this->leftRotate = manager->getBindingKey("leftRotate");
    this->rightRotate = manager->getBindingKey("rightRotate");
    this->pauseDropTimer = manager->getBindingKey("pause");
    this->hold = manager->getBindingKey("hold");
    this->das = manager->getDas();
    this->arr = manager->getArr();
    this->dropDas = manager->getDropDas();
    this->dropArr = manager->getDropArr();
}


void KeyPressManager::startLarr()
{
    this->lArrTimer->start(arr);
}

void KeyPressManager::startRarr()
{
    this->rArrTimer->start(arr);
}

void KeyPressManager::leftEvent()
{
      qDebug()<<"left event";
    this->window->geteTetro()->moveLeft();
}

void KeyPressManager::rightEvent()
{
    qDebug()<<"r event";
    this->window->geteTetro()->movRight();
}

void KeyPressManager::dropEvent()
{
    this->window->geteTetro()->drop();
}
