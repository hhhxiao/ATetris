#ifndef C_H
#define C_H
#include <QColor>
#include <QMap>
#include <QPoint>
#include <QPixmap>

class C
{
public:

    static QMap<QString,int> KEY_MAP;

    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

    static int WIDTH;
    //const value
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
    static const int DIR_L;
    static const int DIR_2;
    static const int DIR_R;
    static const int MAP_WIDTH;
    static const int MAP_HEIGHT;
    static const int CLOCK_WISE;
    static const int CLOCK_ANTI_WISE;

    static const int NO_CLEAR;
    static const int SINGLE;
    static const int DOUBLE;
    static const int TRIGLE;
    static const int TETRIS;
    static const int T_SPIN_SINGLE;
    static const int T_SPIN_DOUBLE;
    static const int T_SPIN_TRIGLE;
    static const int T_SPIN_MINI;
    static const int T_SPIN;
    static const int NO_SPIN;


    static const bool ROTATION;
    static const bool MOVE;
    //rotate Date
    static const QMap<int,QColor> BLOCK_COLOR_LIST;
    static const QVector<QVector<QPoint>> I_WALL_KICK_LIST;
    static const QVector<QVector<QPoint>> OTHER_WALL_KICK_LIST;

    static const QMap<int,QString> LINE_CLEAR_TYPE;

};


#endif // C_H
