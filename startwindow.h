#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "tetromino/tetro.h"
#include "QKeyEvent"
#include "./seq/seq.h"
#include "./mode/gamemode.h"
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE
const int DAS = 100;
const int ARR = 20;
class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
     virtual void keyPressEvent(QKeyEvent *ev);
   // virtual void keyReleaseEvent(QKeyEvent *ev);
public slots:
    //开始重复运动
    void repeatRightMove(){
         //qDebug()<<"repeatRightMove: "<<lastTime;
         if(lastTime <= 0){
                    arrTimer->stop();
                }else if(lastTime > 0){
               tetro->movRight();
                --lastTime;
           }
    }
    void startArr(){
        qDebug()<<"start arr";
        lastTime = 3;
        arrTimer->start(ARR);
    }
    void geneNewTetro();

private:
    Ui::StartWindow *ui;
    GameMap *map;
    Tetromino *tetro;
    QTimer *timer;
    QTimer *dasTimer;
    QTimer *arrTimer;
    int lastTime = 0;
    GameMode mode;
};
#endif // STARTWINDOW_H
