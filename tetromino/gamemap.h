#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include "../data/grid.h"
#include <QPainter>
 enum GRID_FILL{IBLOCK,//I
            TBLOCK,//T
            LBLOCK,//L
            JBLOCK,//J
            OBLOCK,//O
            SBLOCK,//S
            ZBLOCK,//Z
            EMPTY,//empty
            GARBAGE};//garbage line
class GameMap : public QWidget
{
    Q_OBJECT
protected:
       Grid<GRID_FILL> *grids;
       int width;
       int height;
public:
    static int MAP_GRID_WIDTH;
    static int MAP_GRID_HEIGHT;
    static int GRID_WIDTH;


    void paintEvent(QPaintEvent *);
    GameMap(QWidget *parent,int width,int height);
    explicit GameMap(QWidget *parent);
    int getHeight(){return  height;}
    int getWidth(){return  width;}
    bool outOfRange(int x,int y){return  x<0 || x>=width || y <0 || y>=height;}
    bool isEmpty(int x,int y){return grids->get(x,y) == GRID_FILL::EMPTY;}
    ~GameMap();
signals:

};

#endif // GAMEMAP_H
