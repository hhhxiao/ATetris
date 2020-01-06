#include "fortymode.h"
#include "../windows/singlegamewindow.h"
FortyMode::FortyMode():ModeBase()
{
    this->modeName = "40L";
    this->seq = new SevenBagSeq();
}

void FortyMode::gameinitListener()
{
    window->getStatLabel()->setNum(40);
    window->getWdiget()->setBarValue(1.0*window->getStat()->lineClear/40);
}
bool FortyMode::gameWinListener()
{
  return  window->getStat()->lineClear >= 40;
}
void FortyMode::gameStartListener()
{

}

bool FortyMode::gameLoseListener()
{
    return  false;
}

void FortyMode::statUpdateListener()
{
   window->getStatLabel()->setNum(40-window->getStat()->lineClear);
   window->getWdiget()->setBarValue(1.0*window->getStat()->lineClear/40);
}
