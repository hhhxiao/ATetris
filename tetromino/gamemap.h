#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include "../data/grid.h"
#include <QPainter>
#include "c.h"
#include <QtDebug>
#include<QMouseEvent>
class GameMap : public QWidget
{
    Q_OBJECT
protected:
       Grid<int> *grids;
       int width;
       int height;
       bool editAble = false;
       QPoint bwginPoint;
       QPoint endPoint;
       int continusCombo = 0;
public:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent *);
    GameMap(QWidget *parent,int width,int height);
    explicit GameMap(QWidget *parent);
    int getHeight(){return  height;}
    int getWidth(){return  width;}
    bool outOfRange(int x,int y)const{return  x<0 || x>=width || y <0 || y>=height;}
    bool isEmpty(int x,int y)const{return grids->get(x,y) == C::EMPTY;}
    void setGird(int x,int y,int fill){this->grids->set(x,y,fill);}
    void setEdit(bool val){this->editAble = val;}
    ~GameMap();
public slots:
    void clearLine(int spin);
};

#endif // GAMEMAP_H
