#include "tetromino.h"
Tetromino::Tetromino(int type,GameMap *map,QWidget *parent)
    : QWidget(parent),type(type),gameMap(map)
{
    this->lifeTimer = new QTimer(this);  //存活计时器
    this->lifeTimer->setSingleShot(true);
    connect(lifeTimer,SIGNAL(timeout()),SLOT(fix()));
    this->init();
    this->setFixedSize(map->getWidth() * C::WIDTH,map->getHeight()*C::WIDTH);
}


Tetromino::~Tetromino()
{
    delete  this->blocks;
}


//根据方块的类型重置方块
void Tetromino::init()
{
    this->state = C::DIR_0;
    this->y = 0;
    this->willDeath = false;
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

//处死当前方块
void Tetromino::fix(){
    this->blocks->each([this](int dx,int dy,bool value){
        if(value)
            gameMap->setGird(dx+x,dy+y,this->type);
    });
    gameMap->update();
    qDebug()<<"death!!!";
    emit death();
}

//重置方块
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
    painter.drawRect(x*C::WIDTH,y*C::WIDTH,blocks->getWidth()*C::WIDTH,blocks->getHeight()*C::WIDTH);
    painter.setBrush(brush); //添加画刷

    blocks->each([&painter,this](int dx,int dy,bool value){
        if(value)
            painter.drawRect((x+dx)*C::WIDTH,(y+dy)*C::WIDTH,C::WIDTH,C::WIDTH);
    });
}

//左移
void Tetromino::moveLeft()
{
    if(moveable(MoveDirect::M_LEFT)){
        relive();
        --x;
        repaint();
    }

}

//右移
void Tetromino::movRight()
{
    if(moveable(MoveDirect::M_RIGHT))
    {
        relive();
        ++x;
        repaint();
    }
}

//硬降
void Tetromino::hardDrop()
{
    while (moveable(MoveDirect::M_DROP))
    {
        ++y;
    }
    update();
    qDebug()<<"a hard drop";
    fix();
}

//是否可以移动
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
}


//右旋
void Tetromino::rigthRotate()
{
    int result = this->rotateTest(C::CLOCK_WISE);
    if(result == -1)return;

    relive();
    QVector<QPoint> pointList = readPoint(C::CLOCK_WISE);
    this->blocks->rotation();
    qDebug()<<"right offset is : ("<<pointList[result].x()<<","<<pointList[result].y()<<")";
    this->x += pointList[result].x();
    this->y -= pointList[result].y();
    this->state= (this->state+3)%4;
    repaint();
}

//左旋
void Tetromino::leftRotate()
{
    int result = this->rotateTest(C::CLOCK_ANTI_WISE);
    if(result == -1)return;
    relive();
    QVector<QPoint> pointList = readPoint(C::CLOCK_ANTI_WISE);
    this->blocks->antiRotation();
    qDebug()<<"right offset is : ("<<pointList[result].x()<<","<<pointList[result].y()<<")";
    this->x += pointList[result].x();
    this->y -= pointList[result].y();
    this->state = (this->state + 1)%4;
    repaint();
}

//SRS 5个offset 分别测试
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
        //qDebug()<<"test point is("<<pointList[i].x()<<","<<pointList[i].y()<<")";
        if(valid(newPos,this->x + pointList[i].x(),this->y - pointList[i].y())){
            //qDebug()<<"the "<<i<<"test success";
            return i;
        }
    }
    //qDebug()<<"rotate failed";
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

//判断当前位置在地图中是否为合法位置
bool Tetromino::valid(Grid<bool> &grids, int posX, int posY)
{
    bool result = true;
    grids.each([&result,posX,posY,this](int x,int y,bool value){
        if(value){ //如果是方块才判断,空的不判断
            if(gameMap->outOfRange(posX+x,posY+y) ||!gameMap->isEmpty(posX+x,posY+y)){
                result = false;
                return;
            }
        }
    });
    return  result;
}

void Tetromino::drop()
{
    if(moveable(MoveDirect::M_DROP))
    {
        ++y;
        repaint();
    }else{
        if(!willDeath){
            qDebug()<<"要死了QAQ";
            this->lifeTimer->start(deathDelay);
            this->willDeath = true;
        }
    }
}
