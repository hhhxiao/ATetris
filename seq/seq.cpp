#include "seq.h"

void SevenBagSeq::genebag()
{
    static std::default_random_engine e(this->seed);
    static std::uniform_int_distribution<int> u(0,6);
    int arr[7];
    for (int i = 0; i < 7; i++)
        arr[i] = i + 1;
    for (int i = 0; i < 7; i++) {
        int rIndex = u(e);
        int temp = arr[i];
        arr[i] = arr[rIndex];
        arr[rIndex] = temp;
    }
    for (int i = 0; i < 7; i++)
        bag.push_back(arr[i]);
}

int SevenBagSeq::getNext()
{
    int next = bag.front();
   // qDebug()<<"[Seg bag generatorx]  next is "<<next;
    bag.pop_front();
    if (bag.empty()){
      //  qDebug()<<"bag is empty!";
        genebag();
    }
       return next;
}

RepeatSeq::RepeatSeq(const std::initializer_list<int> &list)
{
    for (auto i : list)
        deque.push_back(i);
}

int RepeatSeq::getNext()
{
    int next = deque.front();
    deque.pop_front();
    deque.push_back(next);
    return next;
}
