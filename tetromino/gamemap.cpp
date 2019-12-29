#include "gamemap.h"



GameMap::GameMap(QWidget *parent, int width, int height)
    : QWidget(parent),width(width),height(height)
{
     this->grids = new Grid<GRID_FILL>(width,height,GRID_FILL::EMPTY);
    this->setFixedSize(width * GRID_WIDTH,height*GRID_WIDTH);
}

GameMap::GameMap(QWidget *parent):GameMap(parent,MAP_GRID_WIDTH,MAP_GRID_HEIGHT){}

GameMap::~GameMap()
{
    delete grids;
}

void GameMap::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen());
    for(int x = 0;x<this->width;x++){
        for(int y = 0;y<this->height;y++){
            painter.drawRect(x*GRID_WIDTH,y*GRID_WIDTH,GRID_WIDTH,GRID_WIDTH);
        }
    }
}


int GameMap::MAP_GRID_WIDTH = 10;
int GameMap::MAP_GRID_HEIGHT = 24;
int GameMap::GRID_WIDTH = 32;
