#include "nextwindow.h"
#include "tetromino/tetromino.h"
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
        if(value)painter.drawPixmap(dx*width,dy*width,width,width,*Tetromino::MINO_TEXTURE[type]);
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
