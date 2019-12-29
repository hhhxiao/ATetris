#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "tetromino/tetro.h"
#include "QKeyEvent"
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

private:
    Ui::StartWindow *ui;
    GameMap *map;
    Tetromino *tetro;

};
#endif // STARTWINDOW_H
