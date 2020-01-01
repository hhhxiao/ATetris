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



Grid<bool>* Tetromino::createBlocks( int type,int &x)
{
    Grid<bool>*  blocks;
    if(type == C::I_BLOCK){
        blocks = new Grid<bool>(4,4,false);
        for(int i = 0;i<4;i++)
            blocks->set(i,1,true);
        x = 2;
        //o init
    }else if(type == C::O_BLOCK){
        blocks = new Grid<bool>(2,2,true);
        x = 4;
    }else {
        blocks = new Grid<bool>(3,3,false);
        blocks->set(1,1,true);
        x = 3;
        switch (type) {
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
    return  blocks;
}


//根据方块的类型重置方块
void Tetromino::init()
{
    this->state = C::DIR_0;
    this->y = 0;
    this->willDeath = false;
    this->blocks = createBlocks(this->type,this->x);
}

//处死当前方块
void Tetromino::fix(){
    this->blocks->each([this](int dx,int dy,bool value){
        if(value)
            gameMap->setGird(dx+x,dy+y,this->type);
    });
    gameMap->update();
    //qDebug()<<"death!!!";
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
    pen.setColor(C::BLOCK_COLOR_LIST[this->type]);
    pen.setWidth(2);
    QBrush brush(C::BLOCK_COLOR_LIST[this->type]); //画刷
    painter.setPen(pen); //添加画笔
  //  painter.drawRect(x*C::WIDTH,y*C::WIDTH,blocks->getWidth()*C::WIDTH,blocks->getHeight()*C::WIDTH);

    int ghostY = getGhostY();
    blocks->each([ghostY,&painter,this](int dx,int dy,bool value){
        if(value)
            painter.drawRect((x+dx)*C::WIDTH,(ghostY+dy)*C::WIDTH,C::WIDTH,C::WIDTH);

    });
    painter.setBrush(brush); //添加画刷
    blocks->each([&painter,this](int dx,int dy,bool value){
        if(value)
            painter.drawRect((x+dx)*C::WIDTH,(y+dy)*C::WIDTH,C::WIDTH,C::WIDTH);

    });
}

//左移
void Tetromino::moveLeft()
{
    if(positionValid(*gameMap,*blocks,x-1,y)){
        relive();
        --x;
        repaint();
    }

}

//右移
void Tetromino::movRight()
{
    if(positionValid(*gameMap,*blocks,x+1,y))
    {
        relive();
        ++x;
        repaint();
    }
}

//硬降
void Tetromino::hardDrop(){
    while(positionValid(*gameMap,*blocks,x,y+1))
        ++y;
    update();
    fix();
}

//右旋
void Tetromino::rigthRotate()
{
    //获取旋转测试结果
    auto pair = this->rotateTest(C::CLOCK_WISE);
    if(pair.first == -1)return;//没转成功就直接返回
    relive();
    tspinCheck(pair.first,pair.second,C::CLOCK_WISE);
    this->blocks->rotation();
    this->x += pair.second.x();
    this->y -= pair.second.y();
    this->state= (this->state+3)%4;
    repaint();
}

//左旋
void Tetromino::leftRotate()
{

    auto pair = this->rotateTest(C::CLOCK_ANTI_WISE);
    if(pair.first == -1)return;
    relive();
     tspinCheck(pair.first,pair.second,C::CLOCK_WISE);
    this->blocks->antiRotation();
    this->x += pair.second.x();
    this->y -= pair.second.y();
    this->state = (this->state + 1)%4;
     repaint();
}

int Tetromino::getGhostY()
{
    int pos = y;
    while(positionValid(*gameMap,*blocks,x,pos+1))
        ++pos;
    return pos;
}

void Tetromino::tspinCheck(int num, const QPoint &p, int dir)
{
    if(this->type != C::T_BLOCK)return;
    if(num == 1){
        qDebug()<<"Tspin mini";
        return;
    }
    Grid<bool> testBlcok = *this->blocks;
    if(dir == C::CLOCK_WISE){
        testBlcok.rotation();
    }else {
        testBlcok.antiRotation();
    }
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};
    int result = 0;
    for(int i = 0;i<4;i++){
        if(positionValid(*gameMap,testBlcok,
                         this->x+dx[i]+p.x(),
                         this->y+dy[i]-p.y()
                         ))
            result++;
    }
    if(result == 0){
        qDebug()<<"tspin!!!";
    }
    return;
}

//SRS 5个offset位置分别测试
QPair<int,QPoint> Tetromino::rotateTest(int rotationAngle)
{
    //  qDebug()<<"current state is"<<state;
    QVector<QPoint> pointList = readPoint(rotationAngle);
    Grid<bool> newPos = *blocks;
    //旋转方向
    if(rotationAngle == C::CLOCK_WISE){
        newPos.rotation();
    }else {
        newPos.antiRotation();
    }
    for(int i = 0;i<5;i++){
        if(positionValid(*this->gameMap,newPos,this->x + pointList[i].x(),this->y - pointList[i].y())){
            return {i,pointList[i]};
        }
    }
    return  {-1,QPoint(-100,-100)};
}



//读取判断列表
QVector<QPoint> Tetromino::readPoint(int rotationAngle)
{
    QVector<QVector<QPoint>> table = this->type == C::I_BLOCK?
                C::I_WALL_KICK_LIST:
                C::OTHER_WALL_KICK_LIST;
    return table[this->state * 2 + rotationAngle];
}




void Tetromino::drop()
{
    if(positionValid(*gameMap,*blocks,x,y+1))
    {
        ++y;
        repaint();
    }else{
        if(!willDeath){
            //qDebug()<<"要死了QAQ";
            this->lifeTimer->start(deathDelay);
            this->willDeath = true;
        }
    }
}

//判断某个位置在地图中是否为合法位置
bool Tetromino::positionValid(const GameMap &map, Grid<bool> &grids,int x,int y)
{
    bool result = true;
    grids.each([&result,&x,&y,&map](int dx,int dy,bool value){
        if(value){
            if(value){ //如果是方块才判断,空的不判断
                if(map.outOfRange(dx+x,dy+y) ||!map.isEmpty(dx+x,dy+y)){
                    result = false;
                    return;
                }}

        }
    });
    return result;
}



