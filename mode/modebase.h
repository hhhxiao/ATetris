#ifndef MODEBASE_H
#define MODEBASE_H
#include "../data/grid.h"
#include "../data/stat.h"
#include "../tetromino/tetro.h"
#include "../seq/seq.h"
class ModeBase
{
protected:
    SeqBase *seq;
    GameStat *stat;
    QString modeName;
public:
    ModeBase()=default;
    QString getName(){return  this->modeName;}
    void setStat(GameStat *s){this->stat = s;}
    SeqBase* getSeq(){return  seq;}
    virtual bool cheatEnable() = 0;
    virtual int dropSpeed() = 0;
    virtual bool gameWin(const GameMap&)= 0;
    virtual bool gameLose(const GameMap&)=0;
    virtual bool holdEnable()=0;
    virtual Grid<int> initMap()=0;
};

#endif // MODEBASE_H
