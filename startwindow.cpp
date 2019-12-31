#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{

    ui->setupUi(this);
    map = new GameMap(this);
    tetro = new Tetromino(this->mode.getNextTetro(),map,map);
    connect(tetro,SIGNAL(death()),this,SLOT(geneNewTetro()));
    this->timer = new QTimer(this);
    dasTimer=  new QTimer(this);
    dasTimer->setSingleShot(true);
    arrTimer =  new QTimer(this);
   // connect(dasTimer,SIGNAL(timeout()),this,SLOT(startArr()));
    connect(timer,SIGNAL(timeout()),tetro,SLOT(drop()));
    connect(arrTimer,SIGNAL(timeout()),this,SLOT(repeatRightMove()));
    if(mode.getGravity())
        timer->start(800);
    this->setFixedSize(C::WIDTH*C::MAP_WIDTH+10,C::WIDTH*C::MAP_HEIGHT+10);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Z){
        tetro->leftRotate();
    }if(ev->key() == Qt::Key_X){
        tetro->rigthRotate();
    }if(ev->key() == Qt::Key_Right){
//        if(!ev->isAutoRepeat()){
//            //第一次按动，开始das计时器
//             dasTimer->start(600);
//             tetro->movRight();
//        }else {
//            //不是一次按动，每按动一次给持续右移续一次
//            lastTime+=(int)(ARR*0.09);
   // }
    tetro->movRight();
    }if(ev->key() == Qt::Key_Left){
        tetro->moveLeft();
    }if(ev->key() == Qt::Key_Down){
        tetro->drop();
    }if(ev->key() == Qt::Key_Space){
        //硬降下
        tetro->hardDrop();
       // tetro->setPos(3,0);
        geneNewTetro();
    }
}

//void StartWindow::keyReleaseEvent(QKeyEvent *ev)
//{
//    if(ev->key() == Qt::Key_Right){
//    }

//}

void StartWindow::geneNewTetro()
{
    this->tetro->reset(this->mode.getNextTetro());
}


