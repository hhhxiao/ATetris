#ifndef TETROMINO_H
#define TETROMINO_H

#include <QWidget>
#include "../data/grid.h"
#include "c.h"
#include "gamemap.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
enum MoveDirect{M_LEFT,M_RIGHT,M_DROP};
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
    int y = 0;
    Grid<bool> *blocks;


public:
   void paintEvent(QPaintEvent *);
   Tetromino(int type,GameMap *map, QWidget *parent);
   ~Tetromino();
   void init();
   void reset(int type);
   //operator
   void moveLeft();
   void movRight();
   void hardDrop();
   bool  moveable(MoveDirect direct);
   void rigthRotate();
   void leftRotate();
   void debug(){
       qDebug()<<"pos"<<x<<","<<y;
   }

   void relive(){
       if(this->lifeTimer->isActive()){
           qDebug()<<"关闭死亡定时器";
            this->lifeTimer->stop();
       }
       this->willDeath = false;
        qDebug()<<"又活了!!";
   }
   int rotateTest(int rotationAngle);
   QVector<QPoint> readPoint(int rotationAngle);
   bool valid(Grid<bool> &grids,int x,int y);
   void setPos(int x,int y){this->x = x;this->y = y;repaint();}
public slots:
   void drop();
   void fix();
signals:
    void death(); //死亡信号
};
#endif // TETROMINO_H
