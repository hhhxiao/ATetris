#ifndef BLOODBAR_H
#define BLOODBAR_H

#include <QWidget>
#include "../tetromino/tetro.h"
#include <QPainter>

/**血条类，pixwidth/2   *  pixwidth*20
 * @brief The BloodBar class
 */
class BloodBar : public QWidget
{

    Q_OBJECT
public:
    explicit BloodBar(QWidget *parent = nullptr);
    void setBar(float val){this->val = val;repaint();}
private:
    void paintEvent(QPaintEvent *);
    float val = 0.0;
signals:

};

#endif // BLOODBAR_H
