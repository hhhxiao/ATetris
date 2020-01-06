#include "bloodbar.h"

BloodBar::BloodBar(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(C::WIDTH/2,C::WIDTH*C::MAP_HEIGHT);
}

void BloodBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawRect(0,0,C::WIDTH/2,C::WIDTH*C::MAP_HEIGHT/2);
    QBrush b(Qt::red);
    b.setStyle(Qt::SolidPattern);
    p.setBrush(b);
    p.drawRect(0,C::WIDTH*((1-this->val)*C::MAP_HEIGHT/2),C::WIDTH/2,(C::MAP_HEIGHT/2)*C::WIDTH);
}
