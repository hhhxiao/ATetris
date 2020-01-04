#include "startwindow.h"
#include "ui_startwindow.h"
#include "../mode/fortymode.h"

StartWindow::StartWindow(KeyPressManager* manager,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->modeBase = new FortyMode();
    this->stat = new GameStat();
    this->modeBase->setStat(stat);
    map = new GameMap(this);
    tetro = new Tetromino(1,map,map);
    this->dropTimer = new QTimer(this);
    keyManager = manager;
    keyManager->setWindow(this);
    connect(tetro,SIGNAL(death(int)),this,SLOT(geneNewTetro()));
    connect(tetro,SIGNAL(death(int)),map,SLOT(clearLine(int)));
    connect(tetro,SIGNAL(death(int)),this,SLOT(enableHold()));
    connect(dropTimer,SIGNAL(timeout()),this,SLOT(drop()));
    connect(map,SIGNAL(lineSignal(int)),this,SLOT(statistic(int)));

     for(int i = 0;i<6;i++){
         NextWindow *w = new NextWindow(this,modeBase->getSeq()->getNext());
         w->setGeometry(500,20+120*i,120,120);
        nextWindows.push_back(w);
     }
     holdWindow = new NextWindow(this,C::EMPTY);
     holdWindow->setWidthScale(1.2);
     holdWindow->setGeometry(20,20,120,120);
     nextWindows[0]->setWidthScale(1.2);

     geneNewTetro();
     if(modeBase->cheatEnable()){
         this->map->setEdit(true);
     }

     this->stopwatch = new QTimer(this);
     this->time =QTime(0,0,0);
     connect(stopwatch,SIGNAL(timeout()),SLOT(updateTime()));
     this->map->setFocus();
}

StartWindow::~StartWindow(){
    delete keyManager;
    delete tetro;
    for(auto i:nextWindows)
        delete i;
    delete map;
    delete ui;
    delete dropTimer;
}

void StartWindow::keyPressEvent(QKeyEvent *ev){keyManager->keyPressHandler(ev);}
void StartWindow::keyReleaseEvent(QKeyEvent *ev){keyManager->keyReleaseHanler(ev);}

void StartWindow::wheelEvent(QWheelEvent *event)
{
    if(modeBase->cheatEnable()){
        int currentType = tetro->getType();
        this->tetro->reset( (event->delta()/120+currentType+13)%7+1);
        tetro->repaint();
    }

}
void StartWindow::geneNewTetro(){
    if(modeBase->gameWin(*this->map)){
        this->gameStop(true);
        return;
    }
   // map->clearLine();
    this->tetro->reset(nextWindows[0]->getType());
    int size = nextWindows.size();
    for(int i = 0;i<size-1;i++){
        nextWindows[i]->setType(nextWindows[i+1]->getType());
    }
    nextWindows[size-1]->setType(modeBase->getSeq()->getNext());
}

void StartWindow::drop()
{
    tetro->drop();
}

Tetromino *StartWindow::geteTetro(){return this->tetro;}

GameMap *StartWindow::getMap(){return  this->map;}

void StartWindow::hold()
{
    if(!hasHold){
        if(holdWindow->getType() == C::EMPTY){
            holdWindow->setType(tetro->getType());
            geneNewTetro();
        }
        int type = this->tetro->getType();
        this->tetro->reset(holdWindow->getType());
        tetro->update();
        holdWindow->setType(type);
        hasHold = true;
    }
}

void StartWindow::updateTime(){
    time  = this->time.addSecs(1);
    ui->timerLabel->setText(time.toString("mm:ss.zzz"));
}

void StartWindow::statistic(int lineSignal)
{
    this->stat->addLineClear(lineSignal % 5);
    qDebug()<<C::LINE_CLEAR_TYPE[lineSignal];
}

void StartWindow::gameStart()
{   this->map->setFocus();
    this->dropTimer->start(modeBase->dropSpeed()*1000);
    this->stopwatch->start(1000);
}

void StartWindow::gameStop(bool result)
{
    this->stopwatch->stop();
    qDebug()<<"game end";
}

void StartWindow::on_startBtn_clicked()
{
    if(!hasStart){
        this->gameStart();
    }

}
