#ifndef CCBOT_H
#define CCBOT_H

#include <QObject>
#include "../tetromino/tetro.h"
#include "../seq/seq.h"
extern "C"{
    #include "./ai/coldclear.h"
}
class CCBot
{
private:
    CCAsyncBot *ccbot;
    CCOptions *options;
    CCWeights *weights;
    SeqBase *sequence;
    GameMap *map;
    bool filed[400];
    static QMap<int,CCPiece> minoAdapterList;
public:
    CCMove getNext();
    void syncMap();
    explicit CCBot(GameMap*map, SeqBase *seq);
signals:

};

#endif // CCBOT_H
