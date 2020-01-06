#ifndef C4WMODE_H
#define C4WMODE_H
#include "modebase.h"

class C4wMode:public ModeBase
{
public:
    C4wMode();
    void gameinitListener()override;
    void gameStartListener()override;
    bool gameWinListener()override;
    bool gameLoseListener()override;
    void statUpdateListener()override;
};

#endif // C4WMODE_H
