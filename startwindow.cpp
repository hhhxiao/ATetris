#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    map = new GameMap(this);
    tetro = new IBlock(map,map);

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
        tetro->movRight();
    }if(ev->key() == Qt::Key_Left){
        tetro->moveLeft();
    }if(ev->key() == Qt::Key_Down){
        tetro->drop();
    }

}

