#include "marathonmode.h"
#include "../windows/singlegamewindow.h"
marathonMode::marathonMode()
{
    modeName = "marathon";
    seq = new SevenBagSeq();
}

void marathonMode::gameinitListener()
{

}

void marathonMode::gameStartListener()
{
}

bool marathonMode::gameWinListener()
{
    return  window->getStat()->lineClear >=200;
}

bool marathonMode::gameLoseListener()
{
    return  false;
}

void marathonMode::statUpdateListener()
{

}
