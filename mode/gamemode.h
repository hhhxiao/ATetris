#ifndef GAMEMODE_H
#define GAMEMODE_H
#include <QSet>
#include "../seq/seq.h"
#include "../tetromino/tetro.h"
class GameMode
{
    private:
    QString id;
    QString discription;
    QString name;
    SeqBase *sequence;
    bool gravity = true;
    QSet<LineClearType> filters;
    bool cheatEnale = false;
    int taskNum = 40;
public:
    GameMode();
    int getNextTetro(){
        return this->sequence->getNext();
    }

    bool getGravity(){
        return gravity;
    }
};


#endif // GAMEMODE_H
