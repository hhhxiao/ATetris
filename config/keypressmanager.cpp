#include "keypressmanager.h"
#include "../widget/gamewidget.h"
void KeyPressManager::setGameWidget(GameWidget *widget)
{
    this->gameWidget = widget;
    moveSound = new QSound("./sounds/move.wav");
    rotateSound = new QSound("./sounds/rotate.wav");
    loadSettings();
}

KeyPressManager::KeyPressManager(){
    this->lArrTimer = new QTimer(this);
    this->lDasTimer = new QTimer(this);
    this->rArrTimer = new QTimer(this);
    this->rDasTimer = new QTimer(this);
    this->dropTimer = new QTimer(this);
    lArrTimer->setTimerType(Qt::PreciseTimer);
    lDasTimer->setTimerType(Qt::PreciseTimer);
    rArrTimer->setTimerType(Qt::PreciseTimer);
    rDasTimer->setTimerType(Qt::PreciseTimer);
    lDasTimer->setSingleShot(true);
    rDasTimer->setSingleShot(true);
    connect(lDasTimer,SIGNAL(timeout()),this,SLOT(startLarr()));
    connect(rDasTimer,SIGNAL(timeout()),this,SLOT(startRarr()));
    connect(lArrTimer,SIGNAL(timeout()),this,SLOT(leftEvent()));
    connect(rArrTimer,SIGNAL(timeout()),this,SLOT(rightEvent()));
    connect(dropTimer,SIGNAL(timeout()),this,SLOT(dropEvent()));

}

void KeyPressManager::loadSettings()
{
    /**QMap<QString,int> C::KEY_MAP = {
    {"moveLeft",Qt::Key_Left},
    {"moveRight",Qt::Key_Right},
    {"leftRotate",Qt::Key_Z},
    {"rightRotate",Qt::Key_X},
    {"hardDrop",Qt::Key_Space},
    {"softDrop",Qt::Key_Down},
    {"hold",Qt::Key_Shift},
    {"arr",20},
    {"das",20},
    {"dropArr",20},
    {"lockTime",20}
};
      */
    arr =  C::KEY_MAP["arr"];
    das = C::KEY_MAP["das"];
    dropArr = C::KEY_MAP["dropArr"];

    leftMoveKey = C::KEY_MAP["moveLeft"];
    rightMoveKey = C::KEY_MAP["moveRight"];
    leftRotateKey = C::KEY_MAP["leftRotate"];
    rightRotateKey= C::KEY_MAP["rightRotate"];
    holdKey = C::KEY_MAP["hold"];
    softDropKey = C::KEY_MAP["softDrop"];
    hardDropKey = C::KEY_MAP["hardDrop"];
}

void KeyPressManager::keyPressHandler(QKeyEvent *ev)
{
    if(!ev->isAutoRepeat()){
        if(ev->key() == softDropKey){
                this->dropEvent();
                dropTimer->start(dropArr);
        }else if(ev->key() == leftMoveKey){
                moveSound->play();
                if(rDasTimer->isActive())
                    rDasTimer->stop();
                if(rArrTimer->isActive())
                    rArrTimer->stop();
                this->leftEvent();
                lDasTimer->start(das);
        }else if(ev->key() == rightMoveKey){
            moveSound->play();
            if(lDasTimer->isActive())
                lDasTimer->stop();
            if(lArrTimer->isActive()){
                 lArrTimer->stop();
            }
                this->rightEvent();
                rDasTimer->start(das);
        }else if(ev->key() == hardDropKey){
                qDebug()<<"hard drop pressed!!";
                gameWidget->hardrop();
        }else if(ev->key() == leftRotateKey){
                rotateSound->play();
                gameWidget->lRotate();
        }else if(ev->key() == rightRotateKey){
                rotateSound->play();
                gameWidget->rRotate();
        }
        //else if(ev->key() == this->pauseDropTimer) {
        //}
        else if(ev->key() == holdKey){
                gameWidget->hold();
        }
    }
}

void KeyPressManager::keyReleaseHanler(QKeyEvent *ev)
{
    if(ev->key() == leftMoveKey){
        if(!ev->isAutoRepeat()){
            this->lArrTimer->stop();
            if(this->lDasTimer->isActive()){
                this->lDasTimer->stop();
            }
        }
    }else if(ev->key() == rightMoveKey){
        if(!ev->isAutoRepeat()){
            this->rArrTimer->stop();
            if(this->rDasTimer->isActive()){
                this->rDasTimer->stop();
            }
        }
    }else if(ev->key() == softDropKey){
        if(!ev->isAutoRepeat()){
            if(this->dropTimer->isActive())
                dropTimer->stop();
        }
    }
}

void KeyPressManager::wheelEventHandler(QWheelEvent *ev){}


void KeyPressManager::startLarr(){ this->lArrTimer->start(arr);}

void KeyPressManager::startRarr(){this->rArrTimer->start(arr);}

void KeyPressManager::leftEvent(){gameWidget->moveLeft();}

void KeyPressManager::rightEvent(){gameWidget->moveRight();}

void KeyPressManager::dropEvent(){gameWidget->drop();}
