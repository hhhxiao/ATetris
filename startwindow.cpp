#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{

    ui->setupUi(this);
    map = new GameMap(this);
    tetro = new Tetromino(this->mode.getNextTetro(),map,map);
    this->timer = new QTimer(this);
    if(mode.getGravity())timer->start(800);

    keyManager = new KeyPressManager(this);
    this->setFixedSize(C::WIDTH*C::MAP_WIDTH+10,C::WIDTH*C::MAP_HEIGHT+10);
    connect(tetro,SIGNAL(death()),this,SLOT(geneNewTetro()));
     connect(timer,SIGNAL(timeout()),tetro,SLOT(drop()));
}

StartWindow::~StartWindow(){delete ui;}

void StartWindow::keyPressEvent(QKeyEvent *ev){keyManager->keyPressHandler(ev);}

void StartWindow::keyReleaseEvent(QKeyEvent *ev){keyManager->keyReleaseHanler(ev);}

void StartWindow::geneNewTetro(){this->tetro->reset(this->mode.getNextTetro());}

Tetromino *StartWindow::geteTetro(){return this->tetro;}


