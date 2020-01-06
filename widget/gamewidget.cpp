#include "gamewidget.h"

GameWidget::GameWidget(SeqBase *seqBase,QWidget *parent) : QWidget(parent)
{
    this->seq = seqBase;
    this->setFixedSize(C::WIDTH*22,C::WIDTH*22);
    gameMap = new GameMap(this);
    mino = new Tetromino(1,gameMap,gameMap);
    for (int i = 0;i<6;i++) {
        NextWindow* next = new NextWindow(this,seq->getNext());
        next->setGeometry(C::WIDTH*17,(3*i+1)*C::WIDTH,C::WIDTH*4,C::WIDTH*3);
        this->nextWindows.push_back(next);
    }
    this->holdWindow = new NextWindow(this,7);
    holdWindow->setGeometry(C::WIDTH,C::WIDTH,C::WIDTH*4,C::WIDTH*4);
    b = new BloodBar(this);
    b->setGeometry(C::WIDTH*5.5,C::WIDTH,C::WIDTH/2,C::WIDTH*C::MAP_HEIGHT);
    keyManager = new KeyPressManager();
    keyManager->setGameWidget(this);
    geneNewMino();

    connect(mino,SIGNAL(death(int)),this,SLOT(geneNewMino()));
    connect(mino,SIGNAL(death(int)),gameMap,SLOT(clearLine(int)));
    connect(mino,SIGNAL(death(int)),this,SLOT(enableHold()));
}

void GameWidget::hold()
{
    if(!hasHold){
        if(holdWindow->getType() == C::EMPTY){
            holdWindow->setType(mino->getType());
            geneNewMino();
        }
        int type = mino->getType();
        mino->reset(holdWindow->getType());
        mino->update();
        holdWindow->setType(type);
        hasHold = true;
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event){if(keyManager)keyManager->keyPressHandler(event);}

void GameWidget::keyReleaseEvent(QKeyEvent *event){if(keyManager)keyManager->keyReleaseHanler(event);}

void GameWidget::wheelEvent(QWheelEvent *event){if(keyManager)keyManager->wheelEventHandler(event);}

void GameWidget::geneNewMino()
{
    mino->reset(nextWindows[0]->getType());
    int size = nextWindows.size();
    for(int i = 0;i<size-1;i++)
        nextWindows[i]->setType(nextWindows[i+1]->getType());
    nextWindows[size-1]->setType(seq->getNext());
}
