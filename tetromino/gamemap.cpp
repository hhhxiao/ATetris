#include "gamemap.h"



GameMap::GameMap(QWidget *parent, int width, int height)
    : QWidget(parent),width(width),height(height)
{
     this->grids = new Grid<int>(width,height,C::EMPTY);
    this->setFixedSize(width * C::WIDTH,height*C::WIDTH);
}

GameMap::GameMap(QWidget *parent):GameMap(parent,C::MAP_WIDTH,C::MAP_HEIGHT){}
GameMap::~GameMap(){delete grids;}


void GameMap::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush(Qt::SolidPattern);
    this->grids->each([&painter,&pen,&brush](int x,int y,int tetroType){
        pen.setColor(C::BLOCK_COLOR_LIST[tetroType]);
        brush.setColor(C::BLOCK_COLOR_LIST[tetroType]);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(x*C::WIDTH,y*C::WIDTH,C::WIDTH,C::WIDTH);
    });
}
