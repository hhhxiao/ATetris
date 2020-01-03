#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "tetromino/tetro.h"
#include "QKeyEvent"
#include "../seq/seq.h"
#include "../mode/gamemode.h"
#include "../config/keypressmanager.h"
#include "../widget/nextwindow.h"
#include <QTime>
#include <QTimer>
#include <QSet>
#include <QVector>
QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE
class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow( KeyPressManager *manager,QWidget *parent = nullptr);
    ~StartWindow();
    virtual void keyPressEvent(QKeyEvent *ev);
    virtual void keyReleaseEvent(QKeyEvent *ev); 
    void wheelEvent(QWheelEvent * event);
    Tetromino* geteTetro();
    GameMap *getMap();
    bool cheatEnable(){return  this->mode.cheatEnable();}
    QTimer* getDropTimer(){return  this->dropTimer; }
    GameMode& getGameMode(){return this->mode;}
    void hold();
    bool hasHold = false;
public slots:
    void geneNewTetro();
    void drop();
    void enableHold(){this->hasHold = false;}
    void updateTime();
private slots:
    void on_startBtn_clicked();

private:
    Ui::StartWindow *ui;
    GameMap *map;
    Tetromino *tetro;
    QTimer *dropTimer;
    GameMode mode;
    KeyPressManager *keyManager;
    QVector<NextWindow*> nextWindows;
    NextWindow* holdWindow;
    QTimer *stopwatch;
    QTime *time;
  //  StatisticsPanel *panel;

};
#endif // STARTWINDOW_H
