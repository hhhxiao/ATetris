#ifndef STAT_H
#define STAT_H

#include <QObject>
class GameStat: public QObject
{
    Q_OBJECT
public:
    float lpm = 0;
    float apm = 0;

    int tsd = 0;
    int tst = 0;
    int tsm = 0;
    int tss = 0;
    int b2b = 0;

    int singe = 0;
    int doub = 0;
    int trigle = 0;
    int tetris = 0;
    int maxRen = 0;

    int lineClear = 0;
    int minoPalced = 0;
    GameStat()=default;
public slots:
    void addLineClear(int num){this->lineClear +=num;}
    void addMinoPlace(){this->minoPalced++;}

    void addSingle(){this->singe++;}
    void addDouble(){this->doub++;}
    void addTrigle(){this->trigle++;}
    void addTertis(){this->tetris++;}

    void updateRen(int ren){if(ren > this->maxRen)this->maxRen = ren;}
    void addTsd(){++this->tsd;}
    void addTst(){++this->tst;}
    void addTsm(){++this->tsm;}
    void addTss(){++this->tss;}

};

#endif // STAT_H
