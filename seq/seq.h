#ifndef SEQ_H
#define SEQ_H
#include <random>
#include <QVector>
class Seq
{
public:    
    Seq();
    virtual QVector<int> nextBag() = 0;
};

class SevenBag :public Seq{
private:
    unsigned long seed;
    QVector<int> bag;
    void fillbag();
public:
    SevenBag(unsigned long s);
    SevenBag();
    QVector<int> nextBag()override;
};

#endif // SEQ_H
