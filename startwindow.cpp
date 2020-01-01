#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{

    ui->setupUi(this);
    map = new GameMap(this);
    tetro = new Tetromino(1,map,map);
    this->timer = new QTimer(this);
    if(mode.getGravity())timer->start(800);
    keyManager = new KeyPressManager(this);
    connect(tetro,SIGNAL(death()),this,SLOT(geneNewTetro()));
     connect(timer,SIGNAL(timeout()),tetro,SLOT(drop()));
     for(int i = 0;i<6;i++){
         NextWidnow *w = new NextWidnow(this,mode.getNextTetro());
         w->setGeometry(400,160*i,40*32,40*32);
        nextWindows.push_back(w);
     }
     geneNewTetro();
     //this->setFixedSize(C::WIDTH*C::MAP_WIDTH+10,C::WIDTH*C::MAP_HEIGHT+10);
}

StartWindow::~StartWindow(){
    delete keyManager;
    delete tetro;
    for(auto i:nextWindows)
        delete i;
    delete map;
    delete ui;
    delete timer;
}

void StartWindow::keyPressEvent(QKeyEvent *ev){keyManager->keyPressHandler(ev);}



void StartWindow::keyReleaseEvent(QKeyEvent *ev){keyManager->keyReleaseHanler(ev);}
void StartWindow::geneNewTetro(){


    map->clearLine();
    this->tetro->reset(nextWindows[0]->getType());
    int size = nextWindows.size();
    for(int i = 0;i<size-1;i++){
        nextWindows[i]->setType(nextWindows[i+1]->getType());
    }
       nextWindows[size-1]->setType(mode.getNextTetro());
}

Tetromino *StartWindow::geteTetro(){return this->tetro;}

GameMap *StartWindow::getMap(){return  this->map;}


