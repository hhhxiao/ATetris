#include "tetromino.h"
Tetromino::Tetromino(TetrominoType type,GameMap *map,QWidget *parent)
    : QWidget(parent),type(type),gameMap(map)
{
    this->setFixedSize(map->getWidth(),map->getHeight());
}

void Tetromino::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen; //画笔
    pen.setColor(QColor(0,255, 255));
    pen.setWidth(3);
    QBrush brush(QColor(0, 255, 0, 125)); //画刷
    painter.setPen(pen); //添加画笔
    int blockWidth = GameMap::GRID_WIDTH;
    painter.drawRect(x*blockWidth,y*blockWidth,
                     blocks->getWidth()*blockWidth,blocks->getHeight()*blockWidth);
    painter.setBrush(brush); //添加画刷
    for(int dx = 0;dx<blocks->getWidth();dx++){
        for(int dy = 0;dy<blocks->getHeight();dy++){
        if(blocks->get(dx,dy))
            painter.drawRect((x+dx)*blockWidth,
                             (y+dy)*blockWidth,
                             blockWidth,blockWidth);
        }
    }
}

void Tetromino::moveLeft()
{
    if(moveable(MoveDirect::M_LEFT)){
        --x;
        repaint();
    }

}

void Tetromino::movRight()
{
    if(moveable(MoveDirect::M_RIGHT))
    {
        ++x;
        repaint();
    }


}

bool Tetromino::moveable(MoveDirect direct)
{
    int newX = this->x;
    int newY = this->y;
    switch (direct) {
    case MoveDirect::M_LEFT:
        --newX;
        break;
    case MoveDirect::M_RIGHT:
        ++newX;
        break;
    case MoveDirect::M_DROP:
        ++newY;
        break;
    default:break;
    }
          for(int dx = 0;dx <blocks->getWidth();++dx){
            for(int dy = 0;dy < blocks->getHeight();++dy){
                if(blocks->get(dx,dy)){ //如果是方块才判断,空的不判断
                    //qDebug()<<"x = "<<newX+dx<<"  y="<<newY+dy;
                    if(gameMap->outOfRange(newX+dx,newY+dy) || !gameMap->isEmpty(newX+dx,newY+dy)){
                        qDebug()<<"out of range";
                        return  false;
                    }
                }
            }
          }
    return  true;
}

void Tetromino::rigthRotate()
{
    qDebug()<<"rigthRotate";
    this->blocks->rotation();
    repaint();
}

void Tetromino::leftRotate()
{
    qDebug()<<"antiRotation";
    this->blocks->antiRotation();
     repaint();
}

void Tetromino::drop()
{
    qDebug()<<"Qaq";
    if(moveable(MoveDirect::M_DROP)){
        ++y;
    repaint();
    }
}


QVector<QMap<int,int>> Tetromino::I_WALL_KICK = {
    {{ 0, 0},{-2, 0},{ 1, 0},{-2,-1},{ 1, 2}},
    {{ 0, 0},{ 2, 0},{-1, 0},{ 2, 1},{-1,-2}},
    {{ 0, 0},{-1, 0},{ 2, 0},{-1, 2},{2 ,-1}},
};
