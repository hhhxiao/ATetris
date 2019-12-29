#include "seq.h"

Seq::Seq()
{
}

void SevenBag::fillbag(){
    for(int i = 0;i<7;i++)
        bag[i] = i+1;
}

SevenBag::SevenBag(unsigned long s):Seq(),seed(s)
{
    for(int i = 0;i<7;i++)
        this->bag.push_back(i+1);
}

SevenBag::SevenBag():SevenBag(0){}
QVector<int> SevenBag::nextBag()
{
    fillbag();
    return  this->bag;
}
