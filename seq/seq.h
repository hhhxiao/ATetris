#ifndef SEQ_H
#define SEQ_H
#include <random>
#include <QVector>
#include <ctime>
#include <random>
#include <initializer_list>
#include <deque>
class SeqBase
{
public:
    virtual int getNext() = 0;
};

class SevenBagSeq :public SeqBase {
private:
    std::deque<int> bag;
    int seed;
    void genebag();
public:
    SevenBagSeq() :SevenBagSeq(time(nullptr)) {}
    SevenBagSeq(int seed) :seed(seed) {genebag();}
    int getNext()override;
};

class RepeatSeq :public SeqBase {
private:
    std::deque<int> deque;
public:
    RepeatSeq(const std::initializer_list<int>& list);
    int getNext()override;
};
#endif // SEQ_H
