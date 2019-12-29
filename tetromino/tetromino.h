#ifndef TETROMINO_H
#define TETROMINO_H

#include <QWidget>
#include "../data/grid.h"
#include "gamemap.h"
#include <QPainter>
#include <QDebug>
enum TetrominoType{I,T,L,J,S,Z,O};
enum TetrominoState{ZERO,RIGHT,TWO,LEFT};
enum MoveDirect{M_LEFT,M_RIGHT,M_DROP};
class Tetromino : public QWidget
{
    Q_OBJECT
protected:
    static int WIDTH;
    const TetrominoType type;
    static QVector<QMap<int,int>> I_WALL_KICK;
    QTimer *timer;
    bool fixed;
    TetrominoState state = TetrominoState::ZERO;
    GameMap *gameMap;
    QPixmap *pixmap;
    int x = 0;
    int y = 0;
    Grid<bool> *blocks;
public:
    Tetromino(TetrominoType type,GameMap *map, QWidget *parent);
   bool isFiexd(){return  fixed;}
   void fix(){this->fixed = true;}
   TetrominoType tpye(){return type;}
   void paintEvent(QPaintEvent *);
   void moveLeft();
   void movRight();
   //是否可旋转
//   virtual bool rRotatable() = 0;
//   virtual bool lRotatable() = 0;
//   virtual bool dropable() = 0;
//   virtual void drop() = 0;
//   virtual int rRoate() = 0;
//   virtual int lRotate() = 0;
//   virtual int hardDrop() = 0;
   bool  moveable(MoveDirect direct);
   void rigthRotate();
   void leftRotate();



   void drop();
signals:

};
#endif // TETROMINO_H
