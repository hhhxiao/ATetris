#include "gamemap.h"



GameMap::GameMap(QWidget *parent, int width, int height)
    : QWidget(parent),width(width),height(height)
{
     this->grids = new Grid<int>(width,height,C::EMPTY);
    this->setFixedSize(width * C::WIDTH,height*C::WIDTH);
}

GameMap::GameMap(QWidget *parent):GameMap(parent,C::MAP_WIDTH,C::MAP_HEIGHT){}

GameMap::~GameMap()
{
    delete grids;
}

void GameMap::paintEvent(QPaintEvent *)
{
    qDebug()<<" repaint";
    QPainter painter(this);
    QPen pen;
    QBrush brush(Qt::SolidPattern);
    for(int x = 0;x<this->width;x++){
        for(int y = 0;y<this->height;y++){
             pen.setColor(C::BLOCK_COLOR_LIST[this->grids->get(x,y)]);
            brush.setColor(C::BLOCK_COLOR_LIST[this->grids->get(x,y)]);
           painter.setPen(pen);
           painter.setBrush(brush);
        //    if(this->grids->get(x,y) != C::EMPTY){
            painter.drawRect(x*C::WIDTH,y*C::WIDTH,C::WIDTH,C::WIDTH);
          //  }
           // painter.setBrush(brush);

        }
    }
}
