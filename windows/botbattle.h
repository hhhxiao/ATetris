#ifndef BOTBATTLE_H
#define BOTBATTLE_H

#include <QMainWindow>
#include "../widget/gamewidget.h"
#include "../mode/fortymode.h"
#include "../ai/ccbot.h"
#include <QTimer>
namespace Ui {
class BotBattle;
}

class BotBattle : public QMainWindow
{
    Q_OBJECT

public:
    explicit BotBattle(QWidget *parent = nullptr);
    ~BotBattle();
private:
    Ui::BotBattle *ui;
    GameWidget *playerWidget,*botWidget;
    CCBot *bot;
    QTimer *botTimer;
    CCMove move;
    int moveStep = 0;
private slots:
    void botMove();

};
#endif // BOTBATTLE_H
