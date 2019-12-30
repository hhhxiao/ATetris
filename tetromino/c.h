#ifndef C_H
#define C_H
#include <QColor>
#include <QMap>

class C
{
public:
    static const int WIDTH;
    static const int I_BLOCK;
    static const int T_BLOCK;
    static const int L_BLOCK;
    static const int J_BLOCK;
    static const int S_BLOCK;
    static const int Z_BLOCK;
    static const int O_BLOCK;
    static const int EMPTY;
    static const int GARBAGE;

    static const int DIR_0;
    static const int DIR_R;
    static const int DIR_2;
    static const int DIR_L;
    static const int MAP_WIDTH;
    static const int MAP_HEIGHT;

    static const QMap<int,QColor> BLOCK_COLOR_LIST;
};


#endif // C_H
