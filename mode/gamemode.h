#ifndef GAMEMODE_H
#define GAMEMODE_H
#include <QSet>
#include "../seq/seq.h"
#include "../tetromino/tetro.h"
class GameMode
{
public:
    QString id;
    QString discription;
    QString name;
    Seq *sequence;
    bool gravity = true;
    QSet<LineClearType> filters;
    bool cheatEnale = false;
    int taskNum = 40;
    GameMode();
};

#endif // GAMEMODE_H
