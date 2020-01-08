#ifndef CCBOT_H
#define CCBOT_H
#include "../tetromino/tetro.h"
extern "C"{
    #include "./ai/coldclear.h"
}
#include "../seq/seq.h"
class CCBot
{
private:
    CCAsyncBot *bot;
    CCOptions options;
    CCWeights weights;
    GameMap *map;
    SeqBase *seq;
    bool filed[400];
public:
    static QMap<int,CCPiece> minoAdapterList;
    CCBot(GameMap *map,SeqBase *base);
    CCMove getNextMove();
};

#endif // CCBOT_H
