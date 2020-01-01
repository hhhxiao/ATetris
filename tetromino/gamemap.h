#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include "../data/grid.h"
#include <QPainter>
#include "c.h"
#include <QtDebug>
class GameMap : public QWidget
{
    Q_OBJECT
protected:
       Grid<int> *grids;
       int width;
       int height;
public:
    void paintEvent(QPaintEvent *);
    GameMap(QWidget *parent,int width,int height);
    explicit GameMap(QWidget *parent);
    int getHeight(){return  height;}
    int getWidth(){return  width;}

    bool outOfRange(int x,int y)const{return  x<0 || x>=width || y <0 || y>=height;}
    bool isEmpty(int x,int y)const{return grids->get(x,y) == C::EMPTY;}
    void setGird(int x,int y,int fill){this->grids->set(x,y,fill);}

    void clearLine();
    ~GameMap();
signals:

};

#endif // GAMEMAP_H
