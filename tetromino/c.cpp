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
const int C::DIR_R = 1;
const int C::DIR_2 = 2;
const int C::DIR_L = 3;

//map
const int C::MAP_WIDTH = 10;
const int C::MAP_HEIGHT = 24;
const int C::WIDTH = 32;


//base color
const QMap<int,QColor> C::BLOCK_COLOR_LIST = {
    {C::I_BLOCK,Qt::cyan},
    {C::J_BLOCK,Qt::blue},
    {C::L_BLOCK,Qt::gray},
    {C::S_BLOCK,Qt::green},
    {C::Z_BLOCK,Qt::red},
    {C::O_BLOCK,Qt::yellow},
    {C::T_BLOCK,Qt::magenta},
    {C::GARBAGE,Qt::darkGray},
    {C::EMPTY,  QColor(40,40,40,30)}
};
