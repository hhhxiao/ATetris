#ifndef FORTYMODE_H
#define FORTYMODE_H
#include "modebase.h"

class FortyMode:public ModeBase
{
public:
    FortyMode();
    void gameinitListener()override;
    void gameStartListener()override;
    bool gameWinListener()override;
    bool gameLoseListener()override;
    void statUpdateListener()override;
};

#endif // FORTYMODE_H
