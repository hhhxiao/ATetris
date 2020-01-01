#include "nextwidnow.h"

NextWidnow::NextWidnow(QWidget *parent,int type):QWidget(parent)
{
    int offset;
    this->type = type;
    this->blocks = Tetromino::createBlocks(type,offset);
}

void NextWidnow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawRect(0,0,128,128);
    QBrush brush(C::BLOCK_COLOR_LIST[this->type]);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    blocks->each([&painter](int dx,int dy,bool value){
        if(value)painter.drawRect((dx)*C::WIDTH,(dy)*C::WIDTH,C::WIDTH,C::WIDTH);
    });
}

void NextWidnow::setType(int t)
{
    delete this->blocks;
    int offset;
    this->type = t;
    this->blocks = Tetromino::createBlocks(t,offset);
    repaint();
}
