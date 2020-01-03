#ifndef NEXTWIDNOW_H
#define NEXTWIDNOW_H
#include <QWidget>
#include "tetromino/tetro.h"
#include <QPainter>
class NextWindow:public QWidget
{
    Q_OBJECT
private:
    Grid<bool> *blocks;
    int type;
    float width = C::WIDTH*0.6;
public:
    NextWindow(QWidget*parent,int tetroType);
    void paintEvent(QPaintEvent *);
    int getType(){return  this->type;}
    void setType(int type);
    void setWidthScale(float s){this->width *= s;}
};

#endif // NEXTWIDNOW_H
