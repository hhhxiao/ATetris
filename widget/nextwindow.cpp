#include "nextwindow.h"

NextWindow::NextWindow(QWidget *parent,int type):QWidget(parent)
{
    int offset;
    this->type = type;
    this->blocks = Tetromino::createBlocks(type,offset);
}

void NextWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawRect(0,0,width*4,width*4);
    QBrush brush(C::BLOCK_COLOR_LIST[this->type]);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    blocks->each([this,&painter](int dx,int dy,bool value){
        if(value)painter.drawRect(dx*width,dy*width,width,width);
    });
}

void NextWindow::setType(int t)
{
    delete this->blocks;
    int offset;
    this->type = t;
    this->blocks = Tetromino::createBlocks(t,offset);
    repaint();
}
