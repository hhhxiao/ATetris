#include "gamemap.h"
#include "tetromino.h"


GameMap::GameMap(QWidget *parent, int width, int height)
    : QWidget(parent),width(width),height(height)
{
    this->grids = new Grid<int>(width,height,C::EMPTY);
    this->setGeometry(C::WIDTH*6,C::WIDTH-this->height/2*C::WIDTH,width * C::WIDTH,height*C::WIDTH);
//    this->particleWidget = new QQuickWidget(QUrl::fromLocalFile(":/particle/theme/test.qml"),this);
//    particleWidget->setFixedSize(this->size());
//    particleWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
//    particleWidget->setWindowOpacity(0.5);
    setMouseTracking(true);
}

GameMap::GameMap(QWidget *parent):GameMap(parent,C::MAP_WIDTH,C::MAP_HEIGHT){}



void GameMap::clearLine(int tspin)
{
    qDebug()<<"begin clearLine";
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
        emit ren(continusCombo);
    }

    //这里还有一次死亡判定

    if(line > 0){
        if(tspin == C::NO_SPIN){
            emit lineSignal(line);//没有spin直接发射消行信号
            switch (line) {
            case 2:
                emit attack(1);break;
            case 3:
                emit attack(2);break;
            case 4:
                if(spAttack){
                    emit attack(5);
                }else {
                    spAttack = true;
                    emit attack(4);
                }
                break;
            }
        }else if(tspin == C::T_SPIN_MINI){
            spAttack = true;
            emit(lineSignal(C::T_SPIN_MINI));
        }else if(tspin == C::T_SPIN){
            switch (line) {
            case 1:
                if(spAttack){
                    emit attack(3);
                }else {
                    spAttack = true;
                    emit attack(2);
                }
                break;
            case 2:
                if(spAttack){
                    emit attack(5);
                }else {
                    spAttack = true;
                    emit attack(4);
                }
                break;
            case 3:
                if(spAttack){
                    emit attack(7);
                }else {
                    spAttack = true;
                    emit attack(6);
                }
                break;
            }
            emit lineSignal(5+line);
        }
    }
    emit lineSignal(0);
    qDebug()<<"clearLine finish";
    this->repaint();
}

GameMap::~GameMap(){delete grids;}


//添加垃圾行算法
void GameMap::addGarbageLine(int lineNum)
{
    static std::default_random_engine e(time(nullptr));
    static std::uniform_int_distribution<int> u(0,C::MAP_WIDTH-1);
    int gap = u(e);
    for(int y = 0;y <C::MAP_HEIGHT; ++y){
        if(y <C::MAP_HEIGHT - lineNum){
            for (int x = 0;x < C::MAP_WIDTH;x++) {
                grids->set(x,y,grids->get(x,y+lineNum));
            }
        }else {
            for(int x = 0;x<C::MAP_WIDTH;x++){
                grids->set(x,y,x == gap?C::EMPTY:C::GARBAGE);
            }
        }
    }
    update();
}

void GameMap::syncMap(bool *map)
{
    this->grids->each([map](int dx,int dy,int val){
        if(dy>=20){
        map[(39-dy)*20+dx] = val != C::EMPTY;
        }
    });
}
//paint event
void GameMap::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    this->grids->each([this,&painter](int x,int y,int tetroType){
        if(y >= this->height/2){
              painter.drawPixmap(x*C::WIDTH,y*C::WIDTH,C::WIDTH,C::WIDTH,*Tetromino::MINO_TEXTURE[tetroType]);
        }
    });
}

//编辑模式的鼠标事件
//only dislable cheat
void GameMap::mousePressEvent(QMouseEvent *e)
{
 //   if(this->editAble){
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

   // }

}

//only dislable cheat
void GameMap::mouseMoveEvent(QMouseEvent *e)
{
    this->particleWidget->setFocus();

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

