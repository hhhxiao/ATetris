#ifndef FORTYMODE_H
#define FORTYMODE_H

#include "modebase.h"
#include"../seq/seq.h"
class FortyMode :public ModeBase
{


public:
    FortyMode():ModeBase(){
        this->seq = new SevenBagSeq();
        this->modeName = "40L";
    }
    bool cheatEnable()override{return  true;};
    int dropSpeed() override{return 1;}
    bool gameWin(const GameMap&)override{return stat->lineClear >=40;}
    bool gameLose(const GameMap&)override{return  false;}
    bool holdEnable()override{return  true;}
    Grid<int> initMap() override{return Grid<int>(C::MAP_WIDTH,C::MAP_HEIGHT,C::EMPTY);}
};

#endif // FORTYMODE_H
