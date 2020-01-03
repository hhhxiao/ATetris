#include "gamemap.h"



GameMap::GameMap(QWidget *parent, int width, int height)
    : QWidget(parent),width(width),height(height)
{
    this->grids = new Grid<int>(width,height,C::EMPTY);
    this->setGeometry(130,-this->height/2*C::WIDTH,width * C::WIDTH,height*C::WIDTH);
    setMouseTracking(true);
}

GameMap::GameMap(QWidget *parent):GameMap(parent,C::MAP_WIDTH,C::MAP_HEIGHT){}

void GameMap::clearLine(int spin)
{
    int line =  this->grids->deleteLine([](const QVector<int> &vector){
        for(auto i :vector){
            if(i == C::EMPTY)
                return  false;
        }
        return true;
    },C::EMPTY);

    if(line >0){
        ++continusCombo;
    }else {
        continusCombo = 0;
    }
    if(continusCombo >=2){
        qDebug()<<continusCombo<<" ren!";
    }

    if(line == 4){
        qDebug()<<"Tetris!!";
    }else {
        if(spin == 2){
            qDebug()<<"ts"<<line<<"!!";
        }else {
        qDebug()<<line<<"line clear";
    }
    }
    this->repaint();
}
GameMap::~GameMap(){delete grids;}


void GameMap::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush(Qt::SolidPattern);
    this->grids->each([this,&painter,&pen,&brush](int x,int y,int tetroType){
        pen.setColor(C::BLOCK_COLOR_LIST[tetroType]);
        brush.setColor(C::BLOCK_COLOR_LIST[tetroType]);
        painter.setPen(pen);
        painter.setBrush(brush);
        if(y >= this->height/2)
            painter.drawRect(x*C::WIDTH,y*C::WIDTH,C::WIDTH,C::WIDTH);
    });
}

//only dislable cheat
void GameMap::mousePressEvent(QMouseEvent *e)
{
    if(this->editAble){
        int grid_x = e->pos().x() / C::WIDTH;
        int grid_y = e->pos().y() / C::WIDTH;
        if(!outOfRange(grid_x,grid_y)){
            if(e->button() == Qt::LeftButton){
                this->grids->set(grid_x,grid_y,C::GARBAGE);
            }else if(e->button() == Qt::RightButton){
                this->grids->set(grid_x,grid_y,C::EMPTY);
            }
            update();
        }

    }

}

//only dislable cheat
void GameMap::mouseMoveEvent(QMouseEvent *e)
{

    if(e->buttons()&Qt::LeftButton && editAble){
        int grid_x = e->pos().x() / C::WIDTH;
        int grid_y = e->pos().y() / C::WIDTH;
        if(!outOfRange(grid_x,grid_y)){
              this->grids->set(e->pos().x()/C::WIDTH,e->pos().y()/C::WIDTH,C::GARBAGE);
        }
    }else if(e->buttons()&Qt::RightButton &&editAble){
        int grid_x = e->pos().x() / C::WIDTH;
        int grid_y = e->pos().y() / C::WIDTH;
        if(!outOfRange(grid_x,grid_y)){
              this->grids->set(e->pos().x()/C::WIDTH,e->pos().y()/C::WIDTH,C::EMPTY);
        }
    }
    update();
}

