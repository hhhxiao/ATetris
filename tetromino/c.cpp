#include "c.h"

//tetrominpo type
const int C::I_BLOCK = 1;
const int C::T_BLOCK = 2;
const int C::L_BLOCK = 3;
const int C::J_BLOCK = 4;
const int C::S_BLOCK = 5;
const int C::Z_BLOCK = 6;
const int C::O_BLOCK = 7;

//garbage and empty tile
const int C::GARBAGE = -1;
const int C::EMPTY   = 0;

//tetromino  angle
const int C::DIR_0 = 0;
const int C::DIR_L = 1;
const int C::DIR_2 = 2;
const int C::DIR_R = 3;

//map
const int C::MAP_WIDTH = 10;
const int C::MAP_HEIGHT = 24;
const int C::WIDTH = 32;

const int C::CLOCK_WISE = 1;
const int C::CLOCK_ANTI_WISE = 0;

const int C::SINGLE = 1;
const int C::DOUBLE = 2;
const int C::TRIGLE = 3;
const int C::TETRIS = 4;

//base color
const QMap<int,QColor> C::BLOCK_COLOR_LIST = {
    {C::I_BLOCK,Qt::cyan},
    {C::J_BLOCK,QColor(239,121,33)},
    {C::L_BLOCK,Qt::blue},
    {C::S_BLOCK,Qt::green},
    {C::Z_BLOCK,Qt::red},
    {C::O_BLOCK,Qt::yellow},
    {C::T_BLOCK,Qt::magenta},
    {C::GARBAGE,Qt::darkGray},
    {C::EMPTY,  QColor(40,40,40,30)}
};


//SRS(super rotation system) data support
const QVector<QVector<QPoint>> C::OTHER_WALL_KICK_LIST = {
    { QPoint( 0, 0) ,QPoint	(+1, 0)  ,QPoint(+1,+1)  ,QPoint( 0,-2) ,QPoint	(+1,-2)},//0-L(1) 逆时针
    { QPoint( 0, 0) ,QPoint(-1, 0)	 ,QPoint(-1,+1)	 ,QPoint( 0,-2)	,QPoint(-1,-2)}, //0-R(3) 顺时针

    { QPoint( 0, 0) ,QPoint	(-1, 0)	 ,QPoint(-1,-1)	 ,QPoint( 0,+2) ,QPoint	(-1,+2)},//L(1)-2 逆时针
    { QPoint( 0, 0) ,QPoint	(-1, 0)  ,QPoint(-1,-1)	 ,QPoint( 0,+2) ,QPoint	(-1,+2)},//L(1)-0  顺时针

    { QPoint( 0, 0)	,QPoint(-1, 0)	 ,QPoint(-1,+1)	 ,QPoint( 0,-2) ,QPoint	(-1,-2)},//2-R(3) 逆时针
    { QPoint( 0, 0)	,QPoint(+1, 0)	 ,QPoint(+1,+1)	 ,QPoint( 0,-2) ,QPoint	(+1,-2)},//2-L(1) 顺时针

    { QPoint( 0, 0) ,QPoint	(+1, 0)	 ,QPoint(+1,-1)  ,QPoint( 0,+2) ,QPoint	(+1,+2)},//R(3)-0 逆时针
    { QPoint( 0, 0)	,QPoint(+1, 0)	 ,QPoint(+1,-1)  ,QPoint( 0,+2) ,QPoint	(+1,+2)} //R(3)-2顺时针



};

const QVector<QVector<QPoint>> C::I_WALL_KICK_LIST ={
    {QPoint( 0, 0)	,QPoint(-1, 0)	,QPoint(+2, 0)	,QPoint(-1,+2)	,QPoint(+2,-1)},//0-
    {QPoint( 0, 0)	,QPoint(-2, 0)	,QPoint(+1, 0)	,QPoint(-2,-1)	,QPoint(+1,+2)},//0+

    {QPoint( 0, 0)	,QPoint(-2, 0)	,QPoint(+1, 0)	,QPoint(-2,-1)	,QPoint(+1,+2)},//3-
    {QPoint( 0, 0)	,QPoint(+1, 0)	,QPoint(-2, 0)	,QPoint(+1,-2)	,QPoint(-2,+1)},//3+

    {QPoint( 0, 0)	,QPoint(+1, 0)	,QPoint(-2, 0)	,QPoint(+1,-2)	,QPoint(-2,+1)},//2-
    {QPoint( 0, 0)	,QPoint(+2, 0)	,QPoint(-1, 0)	,QPoint(+2,+1)	,QPoint(-1,-2)},//2+

    {QPoint( 0, 0)	,QPoint(+2, 0)	,QPoint(-1, 0)	,QPoint(+2,+1)	,QPoint(-1,-2)},//1-
    {QPoint( 0, 0)  ,QPoint(-1, 0)	,QPoint(+2, 0)	,QPoint(-1,+2)	,QPoint(+2,-1)}//1+

};

