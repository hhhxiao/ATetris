#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "tetromino/tetro.h"
#include "QKeyEvent"
#include "./seq/seq.h"
#include "./mode/gamemode.h"
#include "./config/keypressmanager.h"
#include "./widget/nextwidnow.h"
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
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    virtual void keyPressEvent(QKeyEvent *ev);
    virtual void keyReleaseEvent(QKeyEvent *ev);
    Tetromino* geteTetro();
    GameMap *getMap();
    bool cheatEnable(){return  this->mode.cheatEnable();}
public slots:
    void geneNewTetro();
private:
    Ui::StartWindow *ui;
    GameMap *map;
    Tetromino *tetro;
    QTimer *timer;
    GameMode mode;
    KeyPressManager *keyManager;
    QVector<NextWidnow*> nextWindows;

};
#endif // STARTWINDOW_H
