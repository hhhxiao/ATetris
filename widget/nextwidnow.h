#ifndef NEXTWIDNOW_H
#define NEXTWIDNOW_H
#include <QWidget>
#include "tetromino/tetro.h"
#include <QPainter>
class NextWidnow:public QWidget
{
    Q_OBJECT
private:
    Grid<bool> *blocks;
    int type;
public:
    NextWidnow(QWidget*parent,int tetroType);
    void paintEvent(QPaintEvent *);
    int getType(){return  this->type;}
    void setType(int type);
};

#endif // NEXTWIDNOW_H
