#include "tetromino.h"
Tetromino::Tetromino(int type,GameMap *map,QWidget *parent)
    : QWidget(parent),type(type),gameMap(map)
{
    this->lifeTimer = new QTimer(this);  //存活计时器
    this->lifeTimer->setSingleShot(true);
    connect(lifeTimer,SIGNAL(timeout()),SLOT(fix()));
    this->init();
    this->setFixedSize(map->getWidth() * C::WIDTH,map->getHeight()*C::WIDTH);
    this->bells = new QSound("./sounds/lock.wav");
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
        x = 3;
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
    this->y = 18;
    this->willDeath = false;
    this->blocks = createBlocks(this->type,this->x);
    bool success = true;
    blocks->each([&success,this](int dx,int dy,bool value){
        if(value && gameMap->get(x+dx,y+dy) != C::EMPTY){
            success = false;
            return ;
        }
    });
    if(!success){
        qDebug()<<"gameOver --- new Mino gene failure";
    }

}

//suo's锁死当前方块
void Tetromino::fix(){
    lifeTimer->stop();
     qDebug()<<"begin fix";
   int tspinResult =  tspinCheck();
    lastTestNumber = -1;
    this->blocks->each([this](int dx,int dy,bool value){
        if(value)
            gameMap->setGird(dx+x,dy+y,this->type);
    });
    bells->play();
    //tspin mini 辅助判定
    qDebug()<<"emit death";
    emit death(tspinResult);
}
int Tetromino::tspinCheck()
{
    //计算是否可移动:
    int spin = C::NO_SPIN;
    if(this->type != C::T_BLOCK || lastTestNumber == -1)return C::NO_SPIN;
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};
    int result = 0;
    for(int i = 0;i<4;i++){
        if(positionValid(*gameMap,*blocks,this->x+dx[i],this->y+dy[i]))
            result++;
    }
    switch (this->lastTestNumber) {
    case 0:
        spin =  result == 0?C::T_SPIN:C::NO_SPIN;
        break;
    case 1:
        spin = C::T_SPIN_MINI;
        break;
    case 2:
        if(this->state == C::DIR_2){
            if(gameMap->get(x,y+2) != C::EMPTY && gameMap->get(x+2,y+2) !=C::EMPTY){
                spin =  C::T_SPIN;
            }else {
                spin = C::T_SPIN_MINI;
            }
        }else if(this->state == C::DIR_0){
            if( this->y < gameMap->getHeight()-2 &&
                    gameMap->get(x,y+2)!=C::EMPTY&&
                    gameMap->get(x+1,y+2)==C::EMPTY&&
                    gameMap->get(x+2,y+2)!=C::EMPTY){
                spin = C::T_SPIN;
            }else {
            spin = C::T_SPIN_MINI;
        }
        }
        break;
    default:
        spin = C::T_SPIN;
    }
        if(spin == C::T_SPIN){
                qDebug()<<"T_spin";
        }else if(spin == C::T_SPIN_MINI){
                qDebug()<<"T_spin mini";
        }else if(spin == C::NO_SPIN) {
            qDebug()<<"NO_spin";

        }
    return  spin;
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
    pen.setWidth(3);
 //   QBrush brush(C::BLOCK_COLOR_LIST[this->type]); //画刷
    painter.setPen(pen); //添加画笔
  //  painter.drawRect(x*C::WIDTH,y*C::WIDTH,blocks->getWidth()*C::WIDTH,blocks->getHeight()*C::WIDTH);

    int ghostY = getGhostY();
    blocks->each([ghostY,&painter,this](int dx,int dy,bool value){
        if(value)
            painter.drawRect((x+dx)*C::WIDTH,(ghostY+dy)*C::WIDTH,C::WIDTH,C::WIDTH);

    });
    blocks->each([&painter,this](int dx,int dy,bool value){
        if(value && y+dy > 19)
            painter.drawPixmap((x+dx)*C::WIDTH,(y+dy)*C::WIDTH,C::WIDTH,C::WIDTH,*MINO_TEXTURE[this->type]);
    });
}

//左移
void Tetromino::moveLeft()
{
    if(positionValid(*gameMap,*blocks,x-1,y)){
        lastTestNumber = -1;
        relive();
        --x;
        repaint();
    }



}

//右移
void Tetromino::moveRight()
{
    if(positionValid(*gameMap,*blocks,x+1,y))
    {
        lastTestNumber = -1;
        relive();
        ++x;
        repaint();
    }
}

//硬降
void Tetromino::hardDrop(){
    qDebug()<<"call hardDrop";
    if(!willDeath){
        while(positionValid(*gameMap,*blocks,x,y+1)){
                 ++y;
        }
    }
    fix();
    update();

}

//右旋
void Tetromino::rigthRotate()
{
    //获取旋转测试结果
    auto pair = this->rotateTest(C::CLOCK_WISE);
    if(pair.first == -1)return;//没转成功就直接返回
    relive();
   // tspinCheck(pair.first,pair.second,C::CLOCK_WISE);
    this->blocks->rotation();
    this->x += pair.second.x();
    this->y -= pair.second.y();
    this->state= (this->state+3)%4;
    this->lastTestNumber = pair.first;
    repaint();
}

//左旋
void Tetromino::leftRotate()
{

    auto pair = this->rotateTest(C::CLOCK_ANTI_WISE);
    if(pair.first == -1)return;
     relive();
    // tspinCheck(pair.first,pair.second,C::CLOCK_WISE);
    this->blocks->antiRotation();
    this->x += pair.second.x();
    this->y -= pair.second.y();
    this->state = (this->state + 1)%4;
    this->lastTestNumber = pair.first;
     repaint();
}

int Tetromino::getGhostY()
{
    int pos = y;
    while(positionValid(*gameMap,*blocks,x,pos+1))
        ++pos;
    return pos;
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
        lastTestNumber = -1; //更新上次的运行状态
        ++y;//y坐标下移一格
        repaint();
    }else{
        if(!willDeath){//计时器还没开始就启动计时器
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

QMap<int,QPixmap*> Tetromino::MINO_TEXTURE = {};
void Tetromino::loadTextures()
{
    QPixmap *p1 = new QPixmap(":/theme/theme/I.png");
    QPixmap *p2 = new QPixmap(":/theme/theme/T.png");
    QPixmap *p3 = new QPixmap(":/theme/theme/O.png");
    QPixmap *p4 = new QPixmap(":/theme/theme/S.png");
    QPixmap *p5 = new QPixmap(":/theme/theme/Z.png");
    QPixmap *p6 = new QPixmap(":/theme/theme/J.png");
    QPixmap *p7 = new QPixmap(":/theme/theme/L.png");
    QPixmap *p8 = new QPixmap(":/theme/theme/EMP.png");
    QPixmap *p9 = new QPixmap(":/theme/theme/GAB.png");
    MINO_TEXTURE.insert(C::I_BLOCK,p1);
    MINO_TEXTURE.insert(C::T_BLOCK,p2);
    MINO_TEXTURE.insert(C::O_BLOCK,p3);
    MINO_TEXTURE.insert(C::S_BLOCK,p4);
    MINO_TEXTURE.insert(C::Z_BLOCK,p5);
    MINO_TEXTURE.insert(C::J_BLOCK,p6);
    MINO_TEXTURE.insert(C::L_BLOCK,p7);
    MINO_TEXTURE.insert(C::EMPTY,  p8);
    MINO_TEXTURE.insert(C::GARBAGE,p9);
}



