#include "keypressmanager.h"
#include "startwindow.h"
void KeyPressManager::setWindow(StartWindow *window){ this->widow = window;}

KeyPressManager::KeyPressManager(StartWindow *win){this->widow = win;}

KeyPressManager::KeyPressManager()=default;

void KeyPressManager::keyPressHandler(QKeyEvent *ev)
{
    if(ev->key() == this->drop){
      widow->geteTetro()->drop();
    }else if(ev->key() == this->moveLeft){
      widow->geteTetro()->moveLeft();
    }else if(ev->key() == this->moveRight){
        widow->geteTetro()->movRight();
    }else if(ev->key() == this->hardDrop){
        widow->geteTetro()->hardDrop();
        widow->geneNewTetro();
    }else if(ev->key() == this->leftRotate){
        widow->geteTetro()->leftRotate();
    }else if(ev->key() == this->rightRotate){
        widow->geteTetro()->rigthRotate();
    }
}

void KeyPressManager::keyReleaseHanler(QKeyEvent *ev)
{
    if(ev->key() == this->drop){

    }else if(ev->key() == this->moveLeft){

    }else if(ev->key() == this->moveRight){

    }else if(ev->key() == this->hardDrop){

    }else if(ev->key() == this->leftRotate){

    }else if(ev->key() == this->rightRotate){

    }

}
