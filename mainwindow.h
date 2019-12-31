#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "startwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_beginGame_clicked();
    void on_test_clicked();

private:
    Ui::MainWindow *ui;
    StartWindow *startWindow;
};

#endif // MAINWINDOW_H
