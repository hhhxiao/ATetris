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
    connect(dropTimer,SIGNAL(timeout()),this,SLOT(drop()));
     for(int i = 0;i<6;i++){
         NextWidnow *w = new NextWidnow(this,mode.getNextTetro());
         w->setGeometry(400,160*i,40*32,40*32);
        nextWindows.push_back(w);
     }
     geneNewTetro();
     if(mode.cheatEnable()){
         this->map->setEdit(true);
     }
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


