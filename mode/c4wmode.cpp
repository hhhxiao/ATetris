#include "c4wmode.h"
#include "fortymode.h"
#include "../windows/singlegamewindow.h"
C4wMode::C4wMode()
{
    this->modeName = "C4W";
    this->seq = new SevenBagSeq();
}

void C4wMode::gameinitListener()
{
    window->getStatLabel()->setNum(0);
    window->getWdiget()->setBarValue(0);
    GameMap *map = window->getWdiget()->getGameMap();
    for(int i = 0;i<C::MAP_HEIGHT;i++){
        for(int j = 0;j<3;j++){
            map->setGird(j,i,C::GARBAGE);
            map->setGird(j+7,i,C::GARBAGE);
        }
    }

    for(int j = 4;j<7;j++)
        map->setGird(j,C::MAP_HEIGHT-1,C::GARBAGE);

}
bool C4wMode::gameWinListener()
{
    return  window->getStat()->lineClear >= 200;
}
void C4wMode::gameStartListener()
{

}

bool C4wMode::gameLoseListener()
{
    return  false;
}

void C4wMode::statUpdateListener()
{
    window->getStatLabel()->setNum(window->getStat()->lineClear);
    window->getWdiget()->setBarValue(1.0*window->getStat()->lineClear/200);
    GameMap *map = window->getWdiget()->getGameMap();
    for(int i = 0;i<C::MAP_HEIGHT;i++){
        for(int j = 0;j<3;j++){
            map->setGird(j,i,C::GARBAGE);
            map->setGird(j+7,i,C::GARBAGE);
        }
    }
}
