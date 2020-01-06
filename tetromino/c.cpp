#include "c.h"



QMap<QString,int> C::KEY_MAP = {
    {"moveLeft",Qt::Key_Left},
    {"moveRight",Qt::Key_Right},
    {"leftRotate",Qt::Key_Z},
    {"rightRotate",Qt::Key_X},
    {"hardDrop",Qt::Key_Space},
    {"softDrop",Qt::Key_Down},
    {"hold",Qt::Key_Shift},
    {"arr",20},
    {"das",20},
    {"dropArr",20},
    {"lockTime",20}
};

int C::SCREEN_WIDTH = 1920;
int C::SCREEN_HEIGHT = 1080;




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
const int C::MAP_HEIGHT = 40;
int C::WIDTH = 35;

const int C::CLOCK_WISE = 1;
const int C::CLOCK_ANTI_WISE = 0;

//line clear
const int C::NO_CLEAR = 0;
const int C::SINGLE = 1;
const int C::DOUBLE = 2;
const int C::TRIGLE = 3;
const int C::TETRIS = 4;

const int C::T_SPIN_SINGLE = 6;
const int C::T_SPIN_DOUBLE = 7;
const int C::T_SPIN_TRIGLE =8;
const int C::T_SPIN_MINI = 11;
//tspin
const int C::NO_SPIN = 0;
const int C::T_SPIN = 2;
const bool C::MOVE = false;
const bool C::ROTATION = true;

//base color
const QMap<int,QColor> C::BLOCK_COLOR_LIST = {
    {C::I_BLOCK,QColor(0,206,209)},
    {C::J_BLOCK,QColor(239,121,33)},
    {C::L_BLOCK,QColor(65,105,225)},
    {C::S_BLOCK,QColor(46,139,87)},
    {C::Z_BLOCK,QColor(220,20,60)},
    {C::O_BLOCK,QColor(255,215,0)},
    {C::T_BLOCK,QColor(148,0,211)},
    {C::GARBAGE,Qt::darkGray},
    {C::EMPTY,  QColor(20,20,20)}
};

const QMap<int,QString> C::LINE_CLEAR_TYPE = {
    {1,"single"},
    {2,"double"},
    {3,"trigle"},
    {4,"tetris"},
    {6,"tss"},
    {7,"tsd"},
    {8,"tst"},
    {11,"t mini"}
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

