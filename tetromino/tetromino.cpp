#include "tetromino.h"
Tetromino::Tetromino(int type,GameMap *map,QWidget *parent)
    : QWidget(parent),type(type),gameMap(map)
{
    this->init();
   this->setFixedSize(map->getWidth() * C::WIDTH,map->getHeight()*C::WIDTH);
}

Tetromino::~Tetromino()
{
    delete  this->blocks;
}

void Tetromino::init()
{
    this->state = C::DIR_0;
    this->y = 0;
    //I init
    if(this->type == C::I_BLOCK){
        this->blocks = new Grid<bool>(4,4,false);
           this->x = 3;
        for(int i = 0;i<4;i++)
            blocks->set(i,1,true);
    //o init
    }else if(this->type == C::O_BLOCK){
        this->x =4;
        this->blocks = new Grid<bool>(2,2,true);
    }else {
        /*
         * const int C::T_BLOCK = 2;
            const int C::L_BLOCK = 3;
            const int C::J_BLOCK = 4;
            const int C::S_BLOCK = 5;
            const int C::Z_BLOCK = 6;
          */
        this->blocks = new Grid<bool>(3,3,false);
        this->x = 3;
        blocks->set(1,1,true);
        switch (this->type) {
        case 2://T
            blocks->set(1,0,true);
            blocks->set(0,1,true);
            blocks->set(2,1,true);
            break;
        case 3://L
            blocks->set(0,1,true);
            blocks->set(2,1,true);
            blocks->set(0,0,true);
            break;
        case 4://J
            blocks->set(0,1,true);
            blocks->set(2,1,true);
            blocks->set(2,0,true);
            break;
        case 5://S
            blocks->set(0,1,true);
            blocks->set(1,0,true);
            blocks->set(2,0,true);
            break;
        case 6://Z
            blocks->set(0,0,true);
            blocks->set(1,0,true);
            blocks->set(2,1,true);
            break;
        }
    }


}

void Tetromino::fix(){
    for(int dx = 0;dx<blocks->getWidth();dx++){
        for(int dy = 0;dy<blocks->getHeight();dy++){
            if(blocks->get(dx,dy)){
                gameMap->setGird(dx+x,dy+y,this->type);
            }
        }
    }
    gameMap->update();
    this->reset(rand()%7+1);
}

void Tetromino::reset(int type)
{
    this->type = type;
    delete  this->blocks;
    this->init();
}

void Tetromino::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen; //画笔
    pen.setColor(QColor(255,255, 255));
    pen.setWidth(2);
    QBrush brush(C::BLOCK_COLOR_LIST[this->type]); //画刷
    painter.setPen(pen); //添加画笔
    int blockWidth = C::WIDTH;
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

void Tetromino::hardDrop()
{
    while (moveable(MoveDirect::M_DROP))
        ++y;
    update();
    qDebug()<<"a hard drop";
    fix();
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

    return  valid(*blocks,newX,newY);
//    for(int dx = 0;dx <blocks->getWidth();++dx){
//        for(int dy = 0;dy < blocks->getHeight();++dy){
//            if(blocks->get(dx,dy)){ //如果是方块才判断,空的不判断
//                //qDebug()<<"x = "<<newX+dx<<"  y="<<newY+dy;
//                if(gameMap->outOfRange(newX+dx,newY+dy) || !gameMap->isEmpty(newX+dx,newY+dy)){
//                    //  qDebug()<<"out of range";
//                    return  false;
//                }
//            }
//        }
//    }
//    return  true;
}

void Tetromino::rigthRotate()
{
    int result = this->rotateTest(C::CLOCK_WISE);
    if(result == -1)return;
    QVector<QPoint> pointList = readPoint(C::CLOCK_WISE);
    this->blocks->rotation();
    qDebug()<<"right offset is : ("<<pointList[result].x()<<","<<pointList[result].y()<<")";
    this->x += pointList[result].x();
    this->y -= pointList[result].y();
    this->state= (this->state+3)%4;
    repaint();
}

void Tetromino::leftRotate()
{
    int result = this->rotateTest(C::CLOCK_ANTI_WISE);
    if(result == -1)return;

    QVector<QPoint> pointList = readPoint(C::CLOCK_ANTI_WISE);
    this->blocks->antiRotation();
     qDebug()<<"right offset is : ("<<pointList[result].x()<<","<<pointList[result].y()<<")";
    this->x += pointList[result].x();
    this->y -= pointList[result].y();
    this->state = (this->state + 1)%4;
    repaint();
}

int Tetromino::rotateTest(int rotationAngle)
{
    qDebug()<<"current state is"<<state;
    QVector<QPoint> pointList = readPoint(rotationAngle);
    Grid<bool> newPos = *blocks;
    //旋转方向
    if(rotationAngle == C::CLOCK_WISE){
        newPos.rotation();
    }else {
        newPos.antiRotation();
    }
    for(int i = 0;i<5;i++){
          qDebug()<<"test point is("<<pointList[i].x()<<","<<pointList[i].y()<<")";
        if(valid(newPos,this->x + pointList[i].x(),this->y - pointList[i].y())){
            qDebug()<<"the "<<i<<"test success";
            return i;
        }
    }
        qDebug()<<"rotate failed";
    return  -1;
}



//读取判断列表
QVector<QPoint> Tetromino::readPoint(int rotationAngle)
{
    QVector<QVector<QPoint>> table = this->type == C::I_BLOCK?
                C::I_WALL_KICK_LIST:
                C::OTHER_WALL_KICK_LIST;
    return table[this->state * 2 + rotationAngle];
}

bool Tetromino::valid(Grid<bool> &grids, int posX, int posY)
{
    for(int dx = 0;dx <grids.getWidth();++dx){
        for(int dy = 0;dy < grids.getHeight();++dy){
            if(grids.get(dx,dy)){ //如果是方块才判断,空的不判断
                if(gameMap->outOfRange(posX+dx,posY+dy) ||
                        !gameMap->isEmpty(posX+dx,posY+dy)){
                    return  false;
                }
            }
        }
    }
    return  true;
}

void Tetromino::drop()
{

    if(moveable(MoveDirect::M_DROP)){
        ++y;
        repaint();
    }
}
