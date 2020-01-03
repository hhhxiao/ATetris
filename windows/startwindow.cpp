#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(KeyPressManager* manager,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{

    ui->setupUi(this);
    map = new GameMap(this);
    tetro = new Tetromino(1,map,map);
    this->dropTimer = new QTimer(this);
    dropTimer->start(800);
    keyManager = manager;
    keyManager->setWindow(this);
    connect(tetro,SIGNAL(death(int)),this,SLOT(geneNewTetro()));
    connect(tetro,SIGNAL(death(int)),map,SLOT(clearLine(int)));
    connect(tetro,SIGNAL(death(int)),this,SLOT(enableHold()));
    connect(dropTimer,SIGNAL(timeout()),this,SLOT(drop()));
     for(int i = 0;i<6;i++){
         NextWindow *w = new NextWindow(this,mode.getNextTetro());
         w->setGeometry(500,20+120*i,120,120);
        nextWindows.push_back(w);
     }
     holdWindow = new NextWindow(this,C::EMPTY);
     holdWindow->setWidthScale(1.2);
     holdWindow->setGeometry(20,20,120,120);
     nextWindows[0]->setWidthScale(1.2);

     geneNewTetro();
     if(mode.cheatEnable()){
         this->map->setEdit(true);
     }

     this->stopwatch = new QTimer(this);
     this->time = new QTime(14,0,0);
    connect(stopwatch,SIGNAL(timeout()),SLOT(updateTime()));
    // panel= new StatisticsPanel(this);
    // panel->setGeometry(600,100,200,200);
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
    if(mode.cheatEnable()){
        int currentType = tetro->getType();
        this->tetro->reset( (event->delta()/120+currentType+13)%7+1);
        tetro->repaint();
    }

}
void StartWindow::geneNewTetro(){
   // map->clearLine();
    this->tetro->reset(nextWindows[0]->getType());
    int size = nextWindows.size();
    for(int i = 0;i<size-1;i++){
        nextWindows[i]->setType(nextWindows[i+1]->getType());
    }
    nextWindows[size-1]->setType(mode.getNextTetro());
}

void StartWindow::drop()
{
    if(mode.getGravity()){
        tetro->drop();
    }
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
    qDebug("time reach");
    auto i= this->time->addSecs(1);
    qDebug()<<time->isValid();
    ui->timerLabel->setText(time->toString("HH,MM,ss"));
}



void StartWindow::on_startBtn_clicked()
{
    this->stopwatch->start(1000);
}
