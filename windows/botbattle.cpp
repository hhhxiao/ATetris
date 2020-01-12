#include "botbattle.h"
#include "ui_botbattle.h"

BotBattle::BotBattle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BotBattle)
{
    ui->setupUi(this);
    SeqBase *seq1 = new SevenBagSeq();
    SeqBase *Seq2 = new RepeatSeq({C::I_BLOCK,C::T_BLOCK,C::L_BLOCK,
                                   C::J_BLOCK,C::S_BLOCK,C::Z_BLOCK,C::O_BLOCK});
    playerWidget = new GameWidget(seq1,this);
    botWidget = new GameWidget(Seq2,this);
    botWidget->move(25*C::WIDTH,2*C::WIDTH);
    playerWidget->setFocus();
    //connect(playerWidget->getGameMap(),SIGNAL(attack(int)),botWidget->getGameMap(),SLOT(addGarbageLine(int)));
    //init bot
    this->ccbot = new CCBot(botWidget->getGameMap(),seq1);
    botTimer = new QTimer(this);
    connect(this->botTimer,SIGNAL(timeout()),this,SLOT(botMove()));
    botTimer->start(200);

}
BotBattle::~BotBattle()
{
    delete ui;
}

void BotBattle::botMove()
{
    if(this->moveStep == 0 || this->moveStep == 127){
        this->move = ccbot->getNext();
        if(move.movement_count == 127){
             qDebug()<<"Widget req failure";
            return;
        }else {
            this->moveStep = move.movement_count;
            }
    }
    qDebug()<<"move Step is "<<moveStep;
    switch (move.movements[move.movement_count-moveStep]) {
    case CC_LEFT:
        botWidget->moveLeft();
        qDebug()<<"bot move left";
        break;
    case CC_RIGHT:
        botWidget->moveRight();
          qDebug()<<"bot move  right";
        break;
    case CC_CW:
        botWidget->lRotate();
          qDebug()<<"bot move lRotate";
        break;
    case CC_CCW:
        botWidget->rRotate();
         qDebug()<<"bot move rRotate";
        break;
    case CC_DROP:
        botWidget->drop();
    qDebug()<<"bot move drop";
        break;
    }
    if(moveStep == 1){
        botWidget->hardrop();
    }
    botWidget->repaint();
    --moveStep;
}


