#ifndef TETROMINO_H
#define TETROMINO_H

#include <QWidget>
#include "../data/grid.h"
#include "c.h"
#include "gamemap.h"
#include <QPainter>
#include <QDebug>
enum MoveDirect{M_LEFT,M_RIGHT,M_DROP};
class Tetromino : public QWidget
{
    Q_OBJECT
public:

protected:

    int type;
    QTimer *timer;
    bool fixed;
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
   void fix();
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


   void setPos(int x,int y){this->x = x;this->y = y;repaint();}
public slots:
   void drop();
signals:

};
#endif // TETROMINO_H
