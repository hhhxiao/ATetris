#include "botbattle.h"
#include "ui_botbattle.h"

BotBattle::BotBattle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BotBattle)
{
    ui->setupUi(this);
    SeqBase *seq1 = new SevenBagSeq();
    SeqBase *Seq2 = new SevenBagSeq(121212);
    SeqBase *Seq3 = new SevenBagSeq(121212);
    playerWidget = new GameWidget(seq1,this);
    botWidget = new GameWidget(Seq2,this);
    botWidget->move(25*C::WIDTH,2*C::WIDTH);
    playerWidget->setFocus();
    bot = new CCBot(botWidget->getGameMap(),Seq3);
    //connect(playerWidget->getGameMap(),SIGNAL(attack(int)),botWidget->getGameMap(),SLOT(addGarbageLine(int)));
    botTimer = new QTimer(this);
    move = bot->getNextMove();

    connect(this->botTimer,SIGNAL(timeout()),this,SLOT(botMove()));
    botTimer->start(300);
}

BotBattle::~BotBattle()
{
    delete ui;
}

void BotBattle::botMove()
{
    if(moveStep ==32){
        moveStep = 0;
    move = bot->getNextMove();
        }//debug

    switch (move.movements[moveStep]) {
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
    botWidget->repaint();
    ++moveStep;
}
