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
    bool cheat = true;
    int taskNum = 40;
public:
    GameMode();
    ~GameMode();
    int getNextTetro(){
        return this->sequence->getNext();
    }

    bool getGravity(){
        return gravity;
    }
    bool cheatEnable(){
        return  this->cheat;
    }

    void gravityToggle(){
        if(cheat)
            this->gravity = !this->gravity;
    }
};


#endif // GAMEMODE_H
