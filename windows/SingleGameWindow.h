#ifndef SINGLEWINDOW_H
#define SINGLEWINDOW_H

#include <QMainWindow>
#include "../widget/gamewidget.h"
#include "../mode/fortymode.h"
#include "../mode/modebase.h"
#include "mode/fortymode.h"
#include "gameoverdialog.h"
#include "../data/stat.h"
#include "../tetromino/tetro.h"
#include <QTime>
#include <QTimer>
#include <QLabel>
namespace Ui {
class SingleGameWindow;
}

class SingleGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SingleGameWindow(ModeBase *base,QWidget *parent = nullptr);
    ~SingleGameWindow();
    GameStat* getStat(){return  stat;}
    QLabel* getStatLabel();
    GameWidget* getWdiget(){return  this->widget;}
    QTimer* getTimer(){return  this->dropTimer;}
public slots:
     void staticUpdate(int);
private:
    //widget
    Ui::SingleGameWindow *ui;
    GameWidget * widget;
    GameOverDialog *overDialog;
    //data
    ModeBase *base;
    bool hasStart = false;
    GameStat *stat;
    QTimer *dropTimer;
    QTimer *stopWatchTimer;
    QTime stopWatch;
    void end();
    void start();
    void gameCheack();
private slots:
    void updateWatch();

};

#endif // SINGLEWINDOW_H
