#ifndef TETROMINO_H
#define TETROMINO_H

#include <QWidget>
#include "../data/grid.h"
#include "c.h"
#include "gamemap.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QPair>
enum MoveDirect{M_LEFT,M_RIGHT,M_DROP,M_UP};
class Tetromino : public QWidget
{
    Q_OBJECT
public:

protected:

    int type;
    int deathDelay = 800;
    QTimer *lifeTimer; //不动到死亡的时间
    bool willDeath = false;
    int state = C::DIR_0;
    GameMap *gameMap;
    QPixmap *pixmap;
    int x = 0;
    int y = 19;
    Grid<bool> *blocks;
    int lastTestNumber = -1;

public:
    void paintEvent(QPaintEvent *);

    //constructor
    Tetromino(int type,GameMap *map, QWidget *parent);
    ~Tetromino();
    void init();
    void reset(int type);
    //operator
    void moveLeft();
    void movRight();
    void hardDrop();
 //   bool  moveable(MoveDirect direct);
    void rigthRotate();
    void leftRotate();
    void relive(){
        if(this->lifeTimer->isActive())
            // qDebug()<<"关闭死亡定时器";
            this->lifeTimer->stop();
        this->willDeath = false;
        //qDebug()<<"又活了!!";
    }

    int getType(){
        return this->type;
    }

    int getGhostY();
    int tspinCheck();
    QPair<int,QPoint> rotateTest(int rotationAngle);
    QVector<QPoint> readPoint(int rotationAngle);
    void setPos(int x,int y){this->x = x;this->y = y;repaint();}
    //static functions
    static Grid<bool>* createBlocks(int type,int &x);
    static bool positionValid(const GameMap &map, Grid<bool> &grids,int x,int y);
public slots:
    void drop();
    void fix();
signals:
    //**
     // 第一个参数是偏移点位
    // 第二个参数是是否可移动
    //第三个点位是固定位对应的方块情况是否是101
    void death(int); //死亡信号
};
#endif // TETROMINO_H
