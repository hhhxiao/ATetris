#include "gamemode.h"

GameMode::GameMode()
{    
    this->sequence = new SevenBagSeq();
}

GameMode::~GameMode()
{
    delete  sequence;
}
