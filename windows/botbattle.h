#ifndef BOTBATTLE_H
#define BOTBATTLE_H

#include <QMainWindow>
#include "../widget/gamewidget.h"
#include "../mode/fortymode.h"
#include <deque>
#include <QTimer>
#include <cstdint>
#include "../ai/ccbot.h"
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
    QTimer *botTimer;
    CCMove move;
    uint8_t moveStep = 0;
    CCBot *ccbot;
   //bot:

private slots:
    void botMove();

};
#endif // BOTBATTLE_H
