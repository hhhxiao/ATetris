#include "gamemap.h"



GameMap::GameMap(QWidget *parent, int width, int height)
    : QWidget(parent),width(width),height(height)
{
    this->grids = new Grid<int>(width,height,C::EMPTY);
    this->setFixedSize(width * C::WIDTH,height*C::WIDTH);
    setMouseTracking(true);
}

GameMap::GameMap(QWidget *parent):GameMap(parent,C::MAP_WIDTH,C::MAP_HEIGHT){}

void GameMap::clearLine()
{
    this->grids->deleteLine([](const QVector<int> &vector){
        for(auto i :vector){
            if(i == C::EMPTY)
                return  false;
        }
        return true;
    },C::EMPTY);
    this->repaint();
}
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

//only dislable cheat
void GameMap::mousePressEvent(QMouseEvent *e)
{
    if(this->editAble){
        int grid_x = e->pos().x() / C::WIDTH;
        int grid_y = e->pos().y() / C::WIDTH;
        if(e->button() == Qt::LeftButton){
            this->grids->set(grid_x,grid_y,C::GARBAGE);
        }else if(e->button() == Qt::RightButton){
            this->grids->set(grid_x,grid_y,C::EMPTY);
        }
        update();
    }

}

//only dislable cheat
void GameMap::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton && editAble){
         this->grids->set(event->pos().x()/C::WIDTH,event->pos().y()/C::WIDTH,C::GARBAGE);
    }else if(event->buttons()&Qt::RightButton &&editAble){
        this->grids->set(event->pos().x()/C::WIDTH,event->pos().y()/C::WIDTH,C::EMPTY);
    }
    update();
}

