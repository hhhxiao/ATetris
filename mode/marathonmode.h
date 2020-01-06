#ifndef MARATHONMODE_H
#define MARATHONMODE_H

#include "modebase.h"
class marathonMode:public ModeBase
{
public:
    marathonMode();
    void gameinitListener()override;
    void gameStartListener()override;
    bool gameWinListener()override;
    bool gameLoseListener()override;
    void statUpdateListener()override;
};

#endif // MARATHONMODE_H
