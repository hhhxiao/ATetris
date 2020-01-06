#ifndef MODEBASE_H
#define MODEBASE_H
#include "../data/grid.h"
#include "../data/stat.h"
#include "../tetromino/tetro.h"
#include "../seq/seq.h"
class SingleGameWindow;
class ModeBase
{
protected:
    SeqBase *seq;
    QString modeName;
    SingleGameWindow *window;
public:
    ModeBase()=default;
    virtual ~ModeBase(){delete seq;}
    QString getName(){return  this->modeName;}
    SeqBase* getSeq(){return  seq;}
    void setStartWindow(SingleGameWindow *w){this->window = w;}

    //listener
    virtual void gameinitListener()=0;
    virtual void gameStartListener()=0;
    virtual bool gameWinListener()= 0;
    virtual bool gameLoseListener()=0;
    virtual void statUpdateListener()=0;
};

#endif // MODEBASE_H
